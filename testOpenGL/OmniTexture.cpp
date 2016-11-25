//
//  OmniTexture.cpp
//  testOpenGL
//
//  Created by takujifunao on 2016/08/08.
//  Copyright © 2016年 takujifunao. All rights reserved.
//

#include "OmniTexture.hpp"

VideoCapture OmniTexture::cap("udpsrc port=5003 ! application/x-rtp, media=(string)video, clock-rate=(int)90000, encoding-name=(string)H264 ! rtph264depay ! avdec_h264 ! videoconvert ! appsink sync=false");

//VideoCapture OmniTexture::cap(0);

//////////////////////////////////////////////////////////////////////


int OmniTexture::GlutInit(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowPosition(posX, posY);
    glutInitWindowSize(sizeX, sizeY);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("testOpenGL");
    return 0;
}


void OmniTexture::TestStart(void){
    
    glutDisplayFunc(Display);
    glutTimerFunc(100, LoopGet, 0);
    glutMainLoop();
    
}


void OmniTexture::LoopGet(int value){
    
    OmniTexture omni;
    omni.GetTextureByOpenCV();
    
    glutPostRedisplay();
    glutTimerFunc(100, LoopGet, 0);
}


void OmniTexture::GetTextureByOpenCV(void){
    
    glDeleteTextures(1, &texture);
    glEnable(GL_TEXTURE_2D);
    
    if (!cap.isOpened()){
        cout << "Cannot open the video cam" << endl;
        return;
    }
    
    bool bSuccess = cap.read(frame);
    if (!bSuccess){
        cout << "Cannot read a frame from video stream" << endl;
        return;
    }
    
    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, frame.data);
    
}


void OmniTexture::Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    DisplayTexture();
    glutSwapBuffers();
}


void OmniTexture::DisplayTexture(void){
    
    static const GLfloat color[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0); glVertex3d(-1.0, -1.0, 0.0);
    glTexCoord2d(1.0, 1.0); glVertex3d(1.0, -1.0, 0.0);
    glTexCoord2d(1.0, 0.0); glVertex3d(1.0, 1.0, 0.0);
    glTexCoord2d(0.0, 0.0); glVertex3d(-1.0, 1.0, 0.0);
    glEnd();
    
}


int OmniTexture::GetTexturePtr(void){
    
    OmniTexture omni;
    omni.GetTextureByOpenCV();
    
    return texture;
}


//////////////////////////////////////////////////////////////////////



