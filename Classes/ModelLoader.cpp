//
// Created by Oleh on 11/18/17.
//

#include "ModelLoader.h"

Editor::EditorRoot *ModelLoader::loadModel(std::string path) {
    return nullptr;
}

void ModelLoader::saveModel(std::string path, Editor::EditorRoot &_root) {
    flatbuffers::FlatBufferBuilder builder;
    std::vector<std::string> textures = {"texture1.png" ,"texture2.png"};

    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> flatTextures=  builder.CreateVectorOfStrings(textures);
    Editor::Vector v(23,13);
    flatbuffers::Offset<flatbuffers::String> className =  builder.CreateString("Super class");

    flatbuffers::Offset<Editor::NodeTree> nodeTree =  Editor::CreateNodeTree(builder,&v, nullptr,Editor::NodeType::NodeType_SPRITE);
    std::vector<flatbuffers::Offset<Editor::NodeTree>> nodeTrees = {nodeTree};
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<Editor::NodeTree>>> flatVector = builder.CreateVector(nodeTrees);
    flatbuffers::Offset<Editor::EditorRoot> root = Editor::CreateEditorRoot(builder,flatTextures,flatVector);
    builder.Finish(root);


    cocos2d::Data data;
    FileUtils::getInstance()->writeDataToFile(data,path);


           // ; builder.GetBufferPointer(),builder.GetSize());

    //Editor::

    //builder.Finish(root);


    //data.fastSet(builder.GetBufferPointer(),builder.GetSize());

}
