#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
#include "serial_sender.h"

int updownServoPos,leftRightServoPos=90;
int midFrameHeight,midFrameWidth;
void adjustCamera(int midx,int midy);

int midScreenWindow = 10;
int stepsize = 1;

int leftRightServo = 1;

serial_sender sender("/dev/ttyUSB0");
int main(int argc, const char** argv)
{

    CascadeClassifier face_cascade,face_cascade_alt;
    face_cascade.load("haarcascade_frontalface_default.xml");
    face_cascade_alt.load("haarcascade_frontalface_alt.xml");

    //setup video capture device and link it to the first capture device
    VideoCapture captureDevice;
    captureDevice.open(1);
    midFrameWidth = captureDevice.get(CV_CAP_PROP_FRAME_WIDTH)/2;
    midFrameHeight = captureDevice.get(CV_CAP_PROP_FRAME_HEIGHT)/2;


    //setup image files used in the capture process
    Mat captureFrame;
    Mat grayscaleFrame;

    //create a window to present the results
    namedWindow("trackerwindow", 1);

    //create a loop to capture and find faces
    while(true)
    {
        //capture a new image frame
        captureDevice>>captureFrame;


        //convert captured image to gray scale and equalize
        cvtColor(captureFrame, grayscaleFrame, CV_BGR2GRAY);
        equalizeHist(grayscaleFrame, grayscaleFrame);

        //create a vector array to store the face found
        vector<Rect> faces;
        //find faces and store them in the vector array
        face_cascade.detectMultiScale(grayscaleFrame, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE, Size(100,100));
        if(faces.size() == 0)
            face_cascade_alt.detectMultiScale(grayscaleFrame,faces,1.2,3,CV_HAAR_FIND_BIGGEST_OBJECT|CV_HAAR_SCALE_IMAGE,Size(80,80));
        //draw a rectangle for all found faces in the vector array on the original image
        for(int i = 0; i < faces.size(); i++)
        {

            Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            Point pt2(faces[i].x, faces[i].y);
            int midFaceY = faces[0].y + (faces[0].height/2);
            int midFaceX = faces[0].x + (faces[0].width/2);

            adjustCamera(midFaceX,midFaceY);
            rectangle(captureFrame, pt1, pt2, cvScalar(0, 255, 0, 0), 1, 8, 0);
            break;
        }

        //print the output
        imshow("trackerwindow", captureFrame);

        //pause for 33ms
        waitKey(33);
    }


    return 0;
}


void adjustCamera(int midx,int midy)
{
    //cout<<midx<<" "<<midy<<endl;
    if(midx < (midFrameWidth-midScreenWindow))
    {
        if(leftRightServoPos >= 5) leftRightServoPos += stepsize;

    }
    else if(midx > midFrameWidth + midScreenWindow)
    {
        if(leftRightServoPos <= 175)
            leftRightServoPos -=stepsize; //Update the pan position variable to move the servo to the right.
    }
    sender.send(leftRightServo,leftRightServoPos);

}



