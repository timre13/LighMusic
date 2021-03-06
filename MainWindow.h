/*
BSD 2-Clause License

Copyright (c) 2021, timre13
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <memory>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Hor_Nice_Slider.H>
#include "Playlist.h"
#include "AboutWindow.h"

/*
 *
 */
class MainWindow final : public Fl_Double_Window
{
private:
    Fl_Text_Buffer *m_trackInfoBuffer{};
    Fl_Text_Display *m_trackInfoW{};

    Fl_Select_Browser *m_playlistW{};

    Fl_Group *m_playlistBtnGrp{};
    Fl_Button *m_addToPlaylistBtn{};
    Fl_Button *m_removeFromPlaylistBtn{};
    Fl_Button *m_clearPlaylistBtn{};
    Fl_Button *m_shufflePlaylistBtn{};

    Fl_Group  *m_ctrlBtnGrp{};
    Fl_Button *m_playPauseBtn{};
    Fl_Button *m_prevTrackBtn{};
    Fl_Button *m_nextTrackBtn{};
    Fl_Button *m_stopBtn{};

    Fl_Text_Buffer *m_timeLabelBuffer{};
    Fl_Text_Display *m_timeLabel{};
    Fl_Hor_Nice_Slider *m_progressBar{};

    Playlist *m_playlistPtr{};

    bool m_isAboutWindowShown{};

    //-------------------------------------------------------------------------

    static void s_tickMusic(void *t) { static_cast<MainWindow*>(t)->tickMusic(); }
    void tickMusic();

    static void s_updateGui(void *t) { static_cast<MainWindow*>(t)->updateGui(); }
    void updateGui();

    inline void setPlayPauseButtonToPlay()
    {
        m_playPauseBtn->copy_label("@>");
        m_playPauseBtn->copy_tooltip("Play");
    }
    inline void setPlayPauseButtonToPause()
    {
        m_playPauseBtn->copy_label("@||");
        m_playPauseBtn->copy_tooltip("Pause");
    }

    //---------------------- Play control button callbacks --------------------

    static void s_playPauseButton_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->playPauseButton_cb();
    }
    void playPauseButton_cb();

    static void s_prevTrackButton_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->prevTrackButton_cb();
    }
    void prevTrackButton_cb();

    static void s_nextTrackButton_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->nextTrackButton_cb();
    }
    void nextTrackButton_cb();

    static void s_stopButton_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->stopButton_cb();
    }
    void stopButton_cb();

    //-------------------------------------------------------------------------

    static void s_playlistWidget_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->playlistWidget_cb();
    }
    void playlistWidget_cb();

    static void s_progressBar_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->progressBar_cb();
    }
    void progressBar_cb();

    //------------------- Playlist control button callbacks -------------------

    static void s_addToPlaylistBtn_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->addToPlaylistBtn_cb();
    }
    void addToPlaylistBtn_cb();

    static void s_removeFromPlaylistBtn_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->removeFromPlaylistBtn_cb();
    }
    void removeFromPlaylistBtn_cb();

    static void s_clearPlaylistBtn_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->clearPlaylistBtn_cb();
    }
    void clearPlaylistBtn_cb();

    static void s_shufflePlaylistBtn_cb(Fl_Widget*, void *t)
    {
        static_cast<MainWindow*>(t)->shufflePlaylistBtn_cb();
    }
    void shufflePlaylistBtn_cb();

    //-------------------------------------------------------------------------

    void showAboutDialog();

public:
    MainWindow(int w, int h, const char *title, Playlist *playlistPtr);
    MainWindow(const MainWindow &other) = delete;
    MainWindow(MainWindow &&other) = delete;
    MainWindow& operator=(const MainWindow &other) = delete;
    MainWindow& operator=(MainWindow &&other) = delete;

    virtual int handle(int event) override;

    ~MainWindow();
};

