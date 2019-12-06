//
//  PSystemGPU.cpp
//  particulasGPU
//
//  Created by Lolo on 04/09/2019.
//

#include "PSystemGPU.hpp"

PSystemGPU::PSystemGPU()
{
    
}

PSystemGPU::~PSystemGPU()
{
    
}
void    PSystemGPU::setup(int   _ammount,string _name)
{
    
     int res = sqrt(_ammount);
     ammount = res*res;
     
     name = _name;
     params.setName(name);
     params.add(ammountLabel.set("Count",ofToString(ammount)));
     
     params.add(lifeMin.set("Life Min",1,1,5));
     params.add(lifeMax.set("Life Max",3,2,10));
     params.add(scaleBorn.set("Scale Born",0.0,0.0,20.0));
     params.add(scaleDead.set("Scale Dead",1.0,0.0,20.0));
     params.add(noiseScale.set("Noise Scale",.1,0.001,2.0));
     params.add(timeScale.set("Time Scale",0.1,0.01,1.5));
     params.add(noisePersist.set("Noise Persist",0.0,1.0,10.0));
     params.add(renderScale.set("Render Scale",300.0,2.0,1000.0));
     

     pPong.setup(res, res);
     vector<float>   position(_ammount*4);
     vector<float>   properties(_ammount*4);

     meshParticles.setMode(OF_PRIMITIVE_POINTS);
     for(int x=0;x<res;x++)
     {
          for(int y=0;y<res;y++)
          {
               unsigned    int index = x+y*res;
               float   dx = x/(float)res;
               float   dy = y/(float)res;
               meshParticles.addVertex(glm::vec3(dx,dy,0.0));
               meshParticles.addTexCoord(glm::vec2(dx,dy));
               position[index*4] = dx;
               position[index*4+1] = dy;
               position[index*4+2] = 0.0;
               position[index*4+3] = 0.0;

               properties[index*4] = 0.0;
               properties[index*4+1] = ofRandom(1.0);
               properties[index*4+2] = 0.0;
               properties[index*4+3] = 1.0;
             
          }
     }
     ofDisableArbTex();

     ofDisableTextureEdgeHack();

     initialPos.loadData(position.data(),res,res,GL_RGBA);
     initialPos.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
     initialPos.setTextureWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

     pPong.set(0,position);
     pPong.set(1,properties);

     ofEnableTextureEdgeHack();
     ofEnableArbTex();

     shaderUpdate.load("shader/update");
     shaderRender.load("shader/render");
}

void    PSystemGPU::update()
{

     ammountLabel = ofToString(ammount);
     
     ofDisableBlendMode();
     pPong.begin();
     shaderUpdate.begin();
     shaderUpdate.setUniformTexture("u_Position", pPong.getSrc().getTexture(0), 0);
     shaderUpdate.setUniformTexture("u_Properties", pPong.getSrc().getTexture(1), 1);
     shaderUpdate.setUniformTexture("u_InitialPos", initialPos, 2);

     shaderUpdate.setUniform2f("u_Res", pPong.getSrc().getWidth(),pPong.getSrc().getHeight());
     shaderUpdate.setUniform1f("u_Time",ofGetElapsedTimef());
     shaderUpdate.setUniform1f("u_Delta",1.0/(float)60.0f);
   
     shaderUpdate.setUniform1f("u_min_Age",lifeMin);
     shaderUpdate.setUniform1f("u_max_Age",lifeMax);
     
     shaderUpdate.setUniform1f("u_noiseScale",noiseScale);
     shaderUpdate.setUniform1f("u_noiseTime",timeScale);
     shaderUpdate.setUniform1f("u_noisePersist",noisePersist);

     pPong.getSrc().getTexture(0).draw(0,0);

     shaderUpdate.end();
     pPong.end();
     
     
}

void    PSystemGPU::draw()
{
    
     ofEnablePointSprites();
     ofEnableAlphaBlending();
     cam.begin();

     shaderRender.begin();
     shaderRender.setUniformTexture("u_Position", pPong.getDst().getTexture(0), 0);
     shaderRender.setUniformTexture("u_Properties", pPong.getDst().getTexture(1), 1);
     shaderRender.setUniform2f("u_Res", pPong.getDst().getWidth(),pPong.getDst().getHeight());
     shaderRender.setUniform3f("u_Scale", renderScale,renderScale,renderScale);
     
     shaderRender.setUniform1f("u_min_Age",lifeMin);
     shaderRender.setUniform1f("u_max_Age",lifeMax);
     shaderRender.setUniform1f("u_Born_Scale",scaleBorn);
     shaderRender.setUniform1f("u_Dead_Scale",scaleDead);

     meshParticles.draw();

     shaderRender.end();


     cam.end();

     ofDisableAlphaBlending();
     ofDisablePointSprites();


     pPong.draw(0,0);
}

void    PSystemGPU::reloadShaders()
{
    shaderUpdate.load("shader/update");
    shaderRender.load("shader/render");
}
