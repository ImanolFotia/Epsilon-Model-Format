#include <iostream>
#include <Model.h>
#include <fstream>
#include <string.h>
#include <string>
#include <emlFormat.h>
#include <ctime>
using namespace std;

bool verboseMode = false;


int main(int argc, char* argv[])
{

    time_t rawtime;
    if(argc < 2)
        return -1;

    if(argc >= 3)
        if(std::string(argv[2]) == "-v")
            verboseMode = true;


    char* pathName = argv[1];
    cout << "taking in: "<< pathName << endl;

    int namePos = std::string(pathName).find(".");
    std::string modelName;
    for(int i = 0 ; i < namePos ; ++i)
        modelName += std::string(pathName).at(i);

    cout << "Output file: " << modelName << ".eml" << endl;

    Model* model = new Model(pathName);

    ofstream FILE(std::string(std::string(modelName) + ".eml").c_str(), ios::binary);
    ifstream inFILE(std::string(std::string(modelName) + ".eml").c_str(), ios::binary);

    t_eml_header h;
    //h.format[0] = 'e';
    //h.format[1] = 'm';
    //h.format[2] = 'l';
    h.format = EMLHEADER;
    h.version = 1.0;
    h.numLumps = 1;

    FILE.write((char*)&h, sizeof(t_eml_header));

    size_t vertices_offset = sizeof(t_eml_header) + sizeof(t_Lumps) * maxLumps;
    t_Lumps *lump = new t_Lumps[3];
    lump[0].offset = vertices_offset;

    size_t indices_offset = sizeof(t_Vertex) * model->meshes.at(0).vertices.size() + sizeof(t_eml_header)+ sizeof(t_Lumps) * maxLumps;
    lump[1].offset = indices_offset;


    size_t texcoords_offset = sizeof(t_Vertex) * model->meshes.at(0).vertices.size() + sizeof(t_eml_header) + sizeof(t_Index) * model->meshes.at(0).indices.size()+ sizeof(t_Lumps) * maxLumps;
    lump[2].offset = texcoords_offset;

    FILE.write((char*)&lump[0], sizeof(t_Lumps));
    FILE.write((char*)&lump[1], sizeof(t_Lumps));
    FILE.write((char*)&lump[2], sizeof(t_Lumps));

    t_Vertex* vert = new t_Vertex[model->meshes.at(0).vertices.size()];
    t_Index* index = new t_Index[model->meshes.at(0).indices.size()];
    t_TexCoord* texCoords = new t_TexCoord[model->meshes.at(0).vertices.size()];

    for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
    {

        vert[i].x = model->meshes.at(0).vertices[i].Position.x;
        vert[i].y = model->meshes.at(0).vertices[i].Position.y;
        vert[i].z = model->meshes.at(0).vertices[i].Position.z;

        if(verboseMode)
        cout << vert[i].y << endl;

        FILE.write((char*)&vert[i], sizeof(t_Vertex));

    }

    for(int i = 0 ; i < model->meshes.at(0).indices.size() ; i++)
    {

        index[i].index = model->meshes.at(0).indices.at(i);

        if(verboseMode)
            cout << index[i].index << endl;

        FILE.write((char*)&index[i], sizeof(t_Index));

    }

    for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
    {

        texCoords[i].s = model->meshes.at(0).vertices[i].TexCoords.x;
        texCoords[i].t = model->meshes.at(0).vertices[i].TexCoords.y;

        if(verboseMode)
            cout <<texCoords[i].s <<endl;

        FILE.write((char*)&texCoords[i], sizeof(t_TexCoord));

    }

    cout << "All Done... :: Closing file" << endl;
    FILE.close();

    ///The following code Opens the file and outputs all the content
#ifdef PROGRAM_DEBUG
        t_eml_header* h3 = new t_eml_header[1];
        t_Lumps lumps[3];
        t_Vertex* vert2 = new t_Vertex[model->meshes.at(0).vertices.size()];
        t_Index* index2 = new t_Index[model->meshes.at(0).indices.size()];
        t_TexCoord* texCoords2 = new t_TexCoord[model->meshes.at(0).vertices.size()];

        inFILE.seekg(0, inFILE.beg);
        for(int i = 0 ; i < 1 ; i++)
        inFILE.read((char*)&h3[i], sizeof(t_eml_header));
        //cout << h3->format << endl;

        inFILE.seekg(sizeof(t_eml_header), inFILE.beg);
        for(int i = 0 ; i < 3 ; i++)
            {
            inFILE.read((char*)&lumps[i], sizeof(t_Lumps));
            //cout << lumps[i].offset << endl;
            }

        inFILE.seekg(lumps[lIndices].offset, inFILE.beg);
        for(int i = 0 ; i < model->meshes.at(0).indices.size() ; i++)
            inFILE.read((char*)&index2[i], sizeof(t_Index));

        for(int i = 0 ; i <  model->meshes.at(0).indices.size() ; i++)
            //cout << index2[i].index << endl;

        inFILE.seekg(lumps[lVertices].offset, inFILE.beg);
        for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
            inFILE.read((char*)&vert2[i], sizeof(t_Vertex));

        for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
            //cout << vert2[i].x << endl;

        inFILE.seekg(lumps[lTexCoords].offset, inFILE.beg);
        for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
            inFILE.read((char*)&texCoords2[i], sizeof(t_TexCoord));

        for(int i = 0 ; i < model->meshes.at(0).vertices.size() ; i++)
            //cout << texCoords2[i].s << endl;


#endif
    delete model;

    return 0;
}
