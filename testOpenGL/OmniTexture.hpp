//
//  OmniTexture.hpp
//  testOpenGL
//
//  Created by takujifunao on 2016/08/08.
//  Copyright © 2016年 takujifunao. All rights reserved.
//

#ifndef OmniTexture_hpp
#define OmniTexture_hpp

////////////////////////////////////
//          import libs
////////////////////////////////////

// standard
#include <iostream>
#include <stdio.h>
#include <unistd.h>

// asynchronous
#include <thread>
#include <future>
#include <functional>

// opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

// opengl
#include <GLUT/glut.h>
#include <OpenGL/gl.h>


////////////////////////////////////
//          name spaces
////////////////////////////////////


using namespace cv;
using namespace std;


//////////////////////////////////////////////////////////////////////

class OmniTexture {
    
private:
    int posX = 1400;
    int posY = 100;
    int sizeX = 1280;
    int sizeY = 640;
    GLuint texture;
    Mat frame;
    VideoCapture static cap;
    
    void GetTextureByOpenCV(void);
    void static LoopGet(int value);
    void static Display(void);
    void static DisplayTexture(void);
    
public:
    int GlutInit(int argc, char* argv[]);
    int GetTexturePtr(void);
    void TestStart(void);
};


#endif /* OmniTexture_hpp */
