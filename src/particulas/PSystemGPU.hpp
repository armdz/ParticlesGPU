//
//  PSystemGPU.hpp
//  particulasGPU
//
//  Created by Lolo on 04/09/2019.
//

#ifndef PSystemGPU_hpp
#define PSystemGPU_hpp

#include <stdio.h>
#include "ofMain.h"
#include "PingPong.hpp"

class PSystemGPU
{
public:
    PSystemGPU();
    ~PSystemGPU();
    void    setup(int   _ammount,string _name);
    void    update();
    void    draw();
    void    reloadShaders();
    ofParameterGroup    getParams(){
        return params;
    };
private:
    string  name;
    int     ammount;
    PingPong    pPong;
    ofShader    shaderUpdate;
    ofShader    shaderRender;

    ofMesh      meshParticles;
    ofTexture   initialPos;
    ofEasyCam   cam;
    
    ofParameterGroup       params;
    ofParameter<string>    ammountLabel;
    ofParameter<int>         lifeMin;
    ofParameter<int>         lifeMax;
    ofParameter<float>       scaleBorn;
    ofParameter<float>       scaleDead;
    ofParameter<float>       noiseScale;
    ofParameter<float>       timeScale;
    ofParameter<float>       noisePersist;

    ofParameter<float>       renderScale;


};

#endif /* PSystemGPU_hpp */
