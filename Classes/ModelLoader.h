//
// Created by Oleh on 11/18/17.
//

#ifndef MYGAME_MODELLOADER_H
#define MYGAME_MODELLOADER_H

#include "cocos2d.h"
#include "EditorRoot_generated.h"
#include "iostream"
USING_NS_CC;

class ModelLoader {
    static Editor::EditorRoot *loadModel(std::string path);
    static void saveModel(std::string path ,Editor::EditorRoot &root);
};


#endif //MYGAME_MODELLOADER_H
