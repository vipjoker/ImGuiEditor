#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CCIMGUI.h"
#include "external/tinydir/tinydir.h"
typedef tinydir_file TFile;
USING_NS_CC;
struct Logger {
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets;        // Index to lines offset
    bool ScrollToBottom;

    void Clear() {
        Buf.clear();
        LineOffsets.clear();
    }

    void AddLog(const char *fmt, ...) IM_PRINTFARGS(2) {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    void Draw(const char *title, bool *p_opened = NULL) {
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiSetCond_FirstUseEver);
        ImGui::Begin(title, p_opened);
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive()) {
            const char *buf_begin = Buf.begin();
            const char *line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++) {
                const char *line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        } else {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};

class ImGuiEditor : public cocos2d::Scene
{
    cocos2d::Sprite *sprite;
    std::vector<TFile> files;
    std::string loadedFile = "";
    std::string currentDir;
    char newFile[256];
public:
    static cocos2d::Scene* createScene();
    Logger logger;
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(ImGuiEditor);

    void guiSetupMenu();
    void showFilesPopup();
    void loadJson();
    void loadFiles(std::string path);
    void drawTreeView();

    void showLoadPopup();
    void showSavePopup();

    bool validateFileName();
};

#endif // __HELLOWORLD_SCENE_H__
