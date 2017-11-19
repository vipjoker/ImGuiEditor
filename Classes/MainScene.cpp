#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "external/json/document.h"
#include "EditorRoot_generated.h"
USING_NS_CC;


#define LOGI(format, ...)      logger.AddLog(format, ##__VA_ARGS__)


Scene *ImGuiEditor::createScene() {
    return ImGuiEditor::create();
}


//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");





bool ImGuiEditor::init() {
    if (!Scene::init()) {
        return false;
    }
    //static Logger loger;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    char *buff = new char[128];
    float *color = new float[3];
    bool *opened = new bool();
    bool *logOpened = new bool(true);
    loadFiles("/Users/oleh/");
    loadJson();




    CCIMGUI::getInstance()->addImGUI([=]() {
        {
            logger.Draw("Example: Log", logOpened);

            guiSetupMenu();
            showLoadPopup();
            showSavePopup();
            drawTreeView();
            //showFilesPopup();

            ImGui::Text("Hello, world!");


            ImGui::InputText("Window title", buff, 255);


            if (ImGui::ColorEdit3("Background color", color)) {
                float r = color[0];
                float g = color[1];
                float b = color[2];


                Director::getInstance()->setClearColor(Color4F(r, g, b, 1));
            }


            ImGui::Begin("Sprite handle");
            int positionx = (int) sprite->getPosition().x;
            ImGui::SliderInt("x position", &positionx, 0, 400);


            int positiony = (int) sprite->getPosition().y;


            ImGui::DragInt("Y position", &positiony);

            ImVec4 vec4;
            ImGui::ValueColor("Color", vec4);


            sprite->setPosition(Vec2(positionx, positiony));




















            // User state
            const int COUNT = 5;
            static const char *items_data[COUNT] = {"Item One", "Item Two", "Item Three", "Item Four", "Item Five"};
            static int items_list[COUNT] = {0, 1, 2, 3, 4};

// Render + dragging
            for (int n = 0; n < COUNT; n++) {
                int item_no = items_list[n];
                ImGui::Selectable(items_data[item_no]);

                if (ImGui::IsItemActive() && !ImGui::IsItemHovered()) {
                    float drag_dy = ImGui::GetMouseDragDelta(0).y;
                    if (drag_dy < 0.0f && n > 0) {
                        // Swap
                        items_list[n] = items_list[n - 1];
                        items_list[n - 1] = item_no;
                        ImGui::ResetMouseDragDelta();
                    } else if (drag_dy > 0.0f && n < COUNT - 1) {
                        items_list[n] = items_list[n + 1];
                        items_list[n + 1] = item_no;
                        ImGui::ResetMouseDragDelta();
                    }
                }
            }


            ImGui::End();


            ImGui::ShowTestWindow(opened);
        }
    }, "demoid");




//

    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(ImGuiEditor::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
                                origin.y + closeItem->getContentSize().height / 2));


    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    sprite = Sprite::create("HelloWorld.png");

    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(sprite, 0);

    return true;
}

void ImGuiEditor::menuCloseCallback(Ref *pSender) {
    CCIMGUI::getInstance()->removeImGUI("demoid");

    //Director::getInstance()->end();


}

void ImGuiEditor::loadFiles(std::string path) {

    //this->files = FileUtils::getInstance()->listFiles(path);
    CCLOG("OPEN path %s", path.c_str());
    this->files.clear();
    tinydir_dir dir;


    tinydir_open(&dir, path.c_str());

    if (path != "/") {
        TFile back;
        unsigned long index = path.rfind("/");
        std::string parent = path.substr(0, index);
        strcpy(back.path, parent.c_str());
        strcpy(back.name, "<-");
        files.push_back(back);

    }


    while (dir.has_next) {
        TFile f;
        tinydir_readfile(&dir, &f);
        files.push_back(f);
        tinydir_next(&dir);

    }
}

void ImGuiEditor::guiSetupMenu() {
    static bool openPopup = false;
    static bool openPopupSave = false;
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open")) openPopup = true;
            if (ImGui::MenuItem("Save")) openPopupSave = true;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Show console")) {}

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    if(openPopupSave){
        ImGui::OpenPopup("Save file");
        openPopupSave = false;
    }

    if (openPopup) {
        ImGui::OpenPopup("Load file");
        openPopup = false;
    }

}

void ImGuiEditor::showLoadPopup() {
    if (ImGui::BeginPopupModal("Load file", NULL)) {
        ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
        ImGui::Columns(2);
        ImGui::Text("Name");
        ImGui::NextColumn();
        ImGui::Text("Path");
        ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::BeginChild("##scrollingregion", ImVec2(500, 300));
        ImGui::Columns(2);
        for (int i = 0; i < files.size(); i++) {

            TFile &f = files[i];
            if (f.name[0] == '.')continue;

            if (ImGui::Selectable(f.name, false, ImGuiSelectableFlags_DontClosePopups)) {
                if (f.is_dir)loadFiles(f.path);
                else loadedFile = f.path;

            }
            ImGui::NextColumn();
            ImGui::Text(f.path);
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::EndChild();;


        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Text(loadedFile.empty() ? "No file selected" : loadedFile.c_str());
        ImGui::PopStyleVar();


        if (ImGui::Button("Load", ImVec2(120, 0))) {
            LOGI(FileUtils::getInstance()->getStringFromFile(loadedFile).c_str());
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void ImGuiEditor::showSavePopup() {
    if (ImGui::BeginPopupModal("Save file", NULL)) {
        ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing() + ImGui::GetStyle().ItemSpacing.y));
        ImGui::Columns(2);
        ImGui::Text("Name");
        ImGui::NextColumn();
        ImGui::Text("Path");
        ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::EndChild();
        ImGui::BeginChild("##scrollingregion", ImVec2(500, 300));
        ImGui::Columns(2);
        for (int i = 0; i < files.size(); i++) {

            TFile &f = files[i];
            if (f.name[0] == '.' || !f.is_dir)continue;

            if (ImGui::Selectable(f.name, false, ImGuiSelectableFlags_DontClosePopups)) {
                loadFiles(f.path);
                currentDir = f.path;


            }
            ImGui::NextColumn();
            ImGui::Text(f.path);
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::EndChild();;


        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::InputText("New file name",newFile,256);
        if(!currentDir.empty()) ImGui::Text("File dir %s  %s",currentDir.c_str(),newFile);
        bool isValid = validateFileName();
        if(!isValid)ImGui::TextColored(ImVec4(1,0,0,1),"Wrong file name");
        else ImGui::TextColored(ImVec4(0,1,0,1),"Correct name");
        ImGui::PopStyleVar();


        if (ImGui::Button("Save", ImVec2(120, 0))) {
            std::string path= currentDir + "/" + newFile;
            FileUtils::getInstance()->writeStringToFile( "Message from editor",path);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

// Usage:

void ImGuiEditor::showFilesPopup() {


    if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        LOGI("SHOW POPUP\n");

        ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
        ImGui::Separator();

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
        ImGui::PopStyleVar();

        if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
        ImGui::EndPopup();
    }
}

void ImGuiEditor::loadJson() {


   const char *json = "{\n"
            "    \"hello\": \"world\",\n"
            "    \"t\": true ,\n"
            "    \"f\": false,\n"
            "    \"n\": null,\n"
            "    \"i\": 123,\n"
            "    \"pi\": 3.1416,\n"
            "    \"a\": [1, 2, 3, 4]\n"
            "}";

    rapidjson::Document document;
    document.Parse(json);

    if(document.HasMember("Ivan")){
        LOGI("Doesn't have ivan");
    }
    if(document.HasMember("hello")){
        LOGI("Have member hello");
    }



}

void ImGuiEditor::drawTreeView() {
    ImGui::Begin("test");
    if (ImGui::TreeNode("Loxel Entities")) {

        if (ImGui::TreeNode("Base")) {
            ImGui::Indent();

            ImGui::Selectable("Num Slots");
            ImGui::Selectable("Count");

            ImGui::Unindent();

            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Slots")) {
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }




    ImGui::Indent();
    ImGui::Selectable("Previous Modifications");
    ImGui::Selectable("Debug Ticks");
    ImGui::Unindent();
    ImGui::End();

}

bool ImGuiEditor::validateFileName() {
    int size = strlen(newFile);
    if (size < 6)return false;

    return (
            newFile[size-1] == 'n' &&
            newFile[size-2] == 'o' &&
            newFile[size-3] == 's' &&
            newFile[size-4] == 'j' &&
            newFile[size-5] == '.'

    );

}

