//
//  ofxDevelopableReader.hpp
//  developability
//
//  Created by kkshmzMBP on 9/21/19.
//

#ifndef ofxDevelopableReader_h
#define ofxDevelopableReader_h

#pragma once

#include "ofMain.h"
#include "ofxEigen.h"
#include "ofxLibigl.h"
#include "ofxDevelopableTypes.h"
class ofxDevelopableReader {
    
public:
    
    ofMesh mesh;
    
    ofxDevelopableReader();
    ~ofxDevelopableReader();
    
    void loadFile(const char *fileName);
    void loadMaterial(bool load=false);
    ofMesh generateMesh();
    ofMesh generateMesh(const OMatrixXs& iV, const OMatrixXi& iF);


    
    typedef struct
    {
        ofIndexType v1,v2,v3;
        ofIndexType vn1,vn2,vn3;
    }
    Index;
    
    typedef struct
    {
        float r;
        float g;
        float b;
    }
    colorRGB;
    
    typedef struct
    {
        colorRGB ambientColor;
        colorRGB diffuseColor;
        colorRGB specularColor;
        float alpha;
    }
    matColor;
    
    std::vector<ofVec3f> vertices;
    std::vector<ofVec3f> normals;
    std::vector<Index> indices;
    
    std::map<int,ofVec3f>faceVertices;
    std::map<int,ofVec3f>faceNormals;
    std::map<string,matColor> materialColors;
    std::map<int,string>materialLocations;
    
    int indexCount;
    int faceCount;
    int materialColorCount;
    int materialCount;
    bool materialBool;
    
    char tempMatName[255];
    matColor tempColor;
    matColor emptyColor;
    
    void parseLine(char *line);
    void parseVertex(char *line);
    void parseNormal(char *line);
    void parseFace(char *line);
    
    void parseMaterialLocation(char *line);
    void parseMaterial(char *line);
    
    void addFace(ofVec3f *vertex, ofVec3f *normal, ofColor *color);
    
    ofColor mapColor(colorRGB vertexColor);
    //adding model
    
    bool loadModel(const char *fileName, OMatrixXs &V, OMatrixXi &F);
    void exportOBJ(ofMesh m,const string name);
//    OMatrixXs V;
//    OMatrixXi F;
    private:
};



#endif /* ofxDevelopableReader_hpp */
