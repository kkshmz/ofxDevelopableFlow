//
//  ofxDevelopableReader.cpp
//  developability
//
//  Created by kkshmzMBP on 9/21/19.
//

#include "ofxDevelopableReader.h"


ofxDevelopableReader::ofxDevelopableReader()
{
    indexCount = 0;
    faceCount = 0;
    materialColorCount = 0;
    materialCount = 0;
    materialBool = false;
}

void ofxDevelopableReader::loadFile(const char *fileName)
{
    //if we're using a material file, load it
    if (materialBool == true)
    {
        ifstream matFile;
        char matLine[255];
        
        char materialFile[255];
        strncpy(materialFile, fileName, sizeof(materialFile));
        strncat(materialFile, ".mtl", sizeof(materialFile) - strlen(materialFile) - 1);
        
        //open file in openframeworks data folder
        matFile.open(ofToDataPath(materialFile).c_str());
        
        if (matFile.is_open())
        {
            while (matFile.getline(matLine, 255))
            {
                parseMaterial(matLine);
            }
        }
        
        matFile.close();
        
    }
    
    //get filename and open corresponding .obj file
    ifstream objFile;
    char line[255];
    
    char objectFile[256];
    strncpy(objectFile, fileName, sizeof(objectFile));
    strncat(objectFile, ".obj", sizeof(objectFile) - strlen(objectFile) - 1);
    
    //open file in openframeworks data folder
    objFile.open(ofToDataPath(objectFile).c_str());
    
    if (objFile.is_open())
    {
        while (objFile.getline(line,256))
        {
            parseLine(line);
        }
    }
    
    objFile.close();
    std::cout << "loaded" << std::endl;
}

void ofxDevelopableReader::loadMaterial(bool load)
{
    if (load == true)
    {
        materialBool = true;
    }
    else
    {
        materialBool = false;
    }
}

void ofxDevelopableReader::parseLine(char *line)
{
    //If empty, don't do anything with it
    if(!strlen(line))
    {
        return;
    }
    
    //get line type identifier from char string
    char *lineType = strtok(strdup(line), " ");
    
    //parse line depending on type
    if (!strcmp(lineType, "usemtl")) // Use Material
    {
        parseMaterialLocation(line);
    }
    else if (!strcmp(lineType, "v")) // Vertices
    {
        parseVertex(line);
    }
    else if (!strcmp(lineType, "vn")) // Normals
    {
        parseNormal(line);
    }
    else if (!strcmp(lineType, "f")) // Indices (Faces)
    {
        parseFace(line);
    }
}

void ofxDevelopableReader::parseVertex(char *line)
{
    float x;
    float y;
    float z;
    
    vertices.push_back(ofVec3f(x,y,z));
    
    //get coordinates from vertex line and assign
    sscanf(line, "v %f %f %f", &vertices.back().x, &vertices.back().y, &vertices.back().z);
}

void ofxDevelopableReader::parseNormal(char *line)
{
    float x;
    float y;
    float z;
    
    normals.push_back(ofVec3f(x,y,z));
    
    //get coordinates from normal line and assign
    sscanf(line, "vn %f %f %f", &normals.back().x, &normals.back().y, &normals.back().z);
}

void ofxDevelopableReader::parseFace(char *line)
{
    //var to hold and discard un-needed texture data
    int discard;
    
    faceCount++;
    
    indices.push_back(Index());
    
    //get vertex and normal indices, discard texture data for now
    if(sscanf(line, "f %d//%d %d//%d %d//%d",
              &indices.back().v1,
              &indices.back().vn1,
              &indices.back().v2,
              &indices.back().vn2,
              &indices.back().v3,
              &indices.back().vn3) <= 1)
    {
        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
               &indices.back().v1,
               &discard,
               &indices.back().vn1,
               &indices.back().v2,
               &discard,
               &indices.back().vn2,
               &indices.back().v3,
               &discard,
               &indices.back().vn3);
    }
}

void ofxDevelopableReader::parseMaterialLocation(char *line)
{
    materialCount++;
    
    char materialName[255];
    
    sscanf(line, "usemtl %s", materialName);
    
    materialLocations[faceCount] = materialName;
}

void ofxDevelopableReader::parseMaterial(char *line)
{
    //If empty, don't do anything with it
    if(!strlen(line))
    {
        return;
    }
    
    //get line type identifier from char string
    char *lineType = strtok(strdup(line), " ");
    
    
    if (!strcmp(lineType, "newmtl")) // Material Name
    {
        sscanf(line, "newmtl %s", tempMatName);
        materialColorCount++;
    }
    else if (!strcmp(lineType, "Ka")) // Ambient Color
    {
        sscanf(line, "Ka %f %f %f", &tempColor.ambientColor.r, &tempColor.ambientColor.g, &tempColor.ambientColor.b);
    }
    else if (!strcmp(lineType, "Kd")) // Diffuse Color
    {
        sscanf(line, "Kd %f %f %f", &tempColor.diffuseColor.r, &tempColor.diffuseColor.g, &tempColor.diffuseColor.b);
    }
    else if (!strcmp(lineType, "Ks")) // Specular Color
    {
        sscanf(line, "Ks %f %f %f", &tempColor.specularColor.r, &tempColor.specularColor.g, &tempColor.specularColor.b);
    }
    else if (!strcmp(lineType, "d")) // Alpha
    {
        sscanf(line, "d %f", &tempColor.alpha);
    }
    else if (!strcmp(lineType, "illum")) // End of material signifier
    {
        //it's the end of this material, so add to material map, and reset vars
        materialColors[tempMatName] = tempColor;
        tempColor = emptyColor;
    }
}

ofMesh ofxDevelopableReader::generateMesh()
{
    int materialCount = materialColors.size();
    int localIndexCount = 0;
    
    ofColor vertColor;
    ofColor defaultColor = ofColor(0.0, 255.0, 0.0);
    
    for (std::vector<Index>::iterator i = indices.begin(); i != indices.end(); ++i)
    {
        if (materialLocations[localIndexCount] != "")
        {
            vertColor = mapColor(materialColors[materialLocations[localIndexCount]].diffuseColor);
        }
        
        //draw triangles
        addFace(&vertices[(i->v1) - 1], &normals[(i->vn1) - 1], &vertColor);
        addFace(&vertices[(i->v2) - 1], &normals[(i->vn2) - 1], &vertColor);
        addFace(&vertices[(i->v3) - 1], &normals[(i->vn3) - 1], &vertColor);
        
        localIndexCount++;
    }
    
    return mesh;
}
ofMesh ofxDevelopableReader::generateMesh(const OMatrixXs& iV, const OMatrixXi& iF)
{
    vector<ofVec3f> vrtx;
//    igl::matrix_to_list(iV, vrtx);

    int materialCount = materialColors.size();
    int localIndexCount = 0;
    
    ofColor vertColor;
    ofColor defaultColor = ofColor(0.0, 255.0, 0.0);
    
    for (std::vector<Index>::iterator i = indices.begin(); i != indices.end(); ++i)
    {
        if (materialLocations[localIndexCount] != "")
        {
            vertColor = mapColor(materialColors[materialLocations[localIndexCount]].diffuseColor);
        }
        
        //draw triangles
        addFace(&vertices[(i->v1) - 1], &normals[(i->vn1) - 1], &vertColor);
        addFace(&vertices[(i->v2) - 1], &normals[(i->vn2) - 1], &vertColor);
        addFace(&vertices[(i->v3) - 1], &normals[(i->vn3) - 1], &vertColor);
        
        localIndexCount++;
    }
    
    return mesh;
}

void ofxDevelopableReader::addFace(ofVec3f *vertex, ofVec3f *normal, ofColor *color)
{
    //temp vars
    int vertIndex;
    int normIndex;
    
    //check if this vertex exists already
    std::map<int,ofVec3f>::iterator faceIt;
    
    for (faceIt = faceVertices.begin(); faceIt != faceVertices.end(); ++faceIt)
    {
        if (faceIt->second == *vertex)
        {
            vertIndex = faceIt->first;
        }
    }
    
    //check if this normal exists already
    std::map<int,ofVec3f>::iterator normIt;
    
    for (normIt = faceNormals.begin(); normIt != faceNormals.end(); ++normIt)
    {
        if (normIt->second == *normal)
        {
            normIndex = normIt->first;
        }
    }
    
    //if a vertex and normal exist at this position, use those aready created
    //otherwise, add new
    if (vertIndex == normIndex)
    {
        mesh.addIndex(vertIndex);
    }
    else
    {
        int currentIndex = indexCount++;
        
        //add vertex
        mesh.addVertex(*vertex);
        faceVertices[currentIndex] = *vertex;
        
        //add color
        mesh.addColor(*color);
        
        //add normal
        mesh.addNormal(*normal);
        faceNormals[currentIndex] = *normal;
        
        //add index
        mesh.addIndex(currentIndex);
    }
    
}

ofColor ofxDevelopableReader::mapColor(colorRGB vertexColor)
{
    float red = ofMap(vertexColor.r, 0.0, 1.0, 0.0, 255.0);
    float green = ofMap(vertexColor.g, 0.0, 1.0, 0.0, 255.0);
    float blue = ofMap(vertexColor.b, 0.0, 1.0, 0.0, 255.0);
    
    ofColor newColor = ofColor(red, green, blue);
    
    return newColor;
}

bool ofxDevelopableReader::loadModel(const char *fileName, OMatrixXs &V, OMatrixXi &F){
    ofxDevelopableReader reader;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    reader.loadFile(fileName);
    mesh = reader.generateMesh();
    //then get V and F and stick it back to the class
    
    const int m = mesh.getVertices().size();
    OMatrixXs vecs;
    // number of columns
    const int n = 3;
    std::cout << m << std::endl;
    std::cout << n << std::endl;
    //    vecs.resize(m,n);
    // Loop over rows
    for(int i = 0;i<m;i++)
    {
        // Loop over cols
        for(int j = 0;j<n;j++)
        {
            vecs(i,j) = mesh.getVertices()[i][j];
            
        }
    }
    
    V = vecs;
    
        const int j = mesh.getIndices().size();
        OMatrixXi faces;
        //number of columns;
        const int k = 3;
    //    faces.resize(j,k);
        for(int x=0;x<j;x++){
            for(int y=0;y<k;y++){
                int tempx = mesh.getIndex(x);
                int tempy = mesh.getIndex(y);
                faces(tempx,tempy);
            }
        }
        F = faces;
    return true;
}

void ofxDevelopableReader::exportOBJ(ofMesh m,const string name){
    ofFile obj;
    obj.open(ofToDataPath(name),ofFile::WriteOnly);
    obj << "#vertices:\n";
    for(int i = 0 ; i < m.getNumVertices(); i++) {
        ofVec3f v = m.getVertex(i);
        obj << "v " + ofToString(v.x) + " " + ofToString(v.y) + " " + ofToString(v.z) + "\n";
    }
    obj << "#faces:\n";
    for(int i = 0 ; i < m.getNumIndices(); i += 3)
        obj << "f " + ofToString(m.getIndex(i)+1) + " " + ofToString(m.getIndex(i+1)+1) + " " + ofToString(m.getIndex(i+2)+1) + "\n";
    obj << "\n";
    obj.close();
    cout << "wrote " << name << endl;
}

ofxDevelopableReader::~ofxDevelopableReader()
{
    //
}

