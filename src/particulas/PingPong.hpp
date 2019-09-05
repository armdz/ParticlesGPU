//
//  PingPong.hpp
//  particulasGPU
//
//  Created by Lolo on 04/09/2019.
//

#ifndef PingPong_hpp
#define PingPong_hpp

#include <stdio.h>
#include "ofMain.h"

class PingPong {
    
public:
    PingPong(){
        src = nullptr;
        dst = nullptr;
    };
    ~PingPong(){};
    
    void    setup(int   _w,int  _h)
    {
        res = _w;
        ofFbo::Settings settings;
        settings.width = _w;
        settings.height = _h;
        settings.internalformat = GL_RGBA32F;
        settings.numColorbuffers = 2;
        settings.textureTarget = GL_TEXTURE_2D;
        settings.wrapModeHorizontal = GL_CLAMP_TO_EDGE;
        settings.wrapModeVertical = GL_CLAMP_TO_EDGE;
        settings.useDepth = false;
        
        for(int i=0;i<2;i++){
            fbo[i].allocate(settings);
            for(int j=0;j<settings.numColorbuffers;j++){
                fbo[i].getTexture(j).setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
            }
            fbo[i].begin();
            fbo[i].activateAllDrawBuffers();
            ofClear(0,0);
            fbo[i].end();
        }
        src = &fbo[0];
        dst = &fbo[1];
    };
    
    void    set(int _index,vector<float>   _data)
    {
        fbo[0].getTexture(_index).loadData(_data.data(), res, res, GL_RGBA);
        fbo[1].getTexture(_index).loadData(_data.data(), res, res, GL_RGBA);
    }
    
    void    draw(int _x,float _y)
    {
        
        float size = 150;
        ofPushMatrix();
        ofTranslate(_x,_y);
        for(int j=0;j<2;j++){
            for(int i=0;i<fbo[j].getNumTextures();i++)
            {
                ofSetColor(255);
                fbo[j].getTexture(i).draw(i*size,j*size,size,size);
                ofSetColor(0);
                ofNoFill();
                ofDrawRectangle(i*size,j*size,size,size);
            }
        }
        ofPopMatrix();
        
       
        ofSetColor(0);
        ofNoFill();
        ofDrawRectangle(_x,_y,size,size);
        
        ofSetColor(255);
        dst->draw(_x,_y+size,size,size);
        
        ofSetColor(0);
        ofNoFill();
        ofDrawRectangle(_x,_y+size,size,size);
    }
    
    void    begin()
    {
        dst->begin();
        dst->activateAllDrawBuffers();
    }
    
    void    end()
    {
        dst->end();
        std::swap(src,dst);
    }
    
    ofFbo   getSrc()
    {
        return *src;
    };
    ofFbo   getDst()
    {
        return *dst;
    };
    
private:
  
    
    ofFbo   fbo[2];
    ofFbo   *src;
    ofFbo   *dst;
    int     res;
};


#endif /* PingPong_hpp */
