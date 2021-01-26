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

#include "Playlist.h"
#include <iostream>

Playlist::Playlist(const std::string &audioDevName)
    : m_audioDevName{audioDevName}
{
}

void Playlist::openTrackAtIndex(size_t index)
{
    // If playlist is empty
    if (m_filePaths.size() < 1)
        return;

    // If index if out of range
    if (index >= m_filePaths.size())
    {
        std::cerr << "Failed to open music, invalid index" << '\n';
        return;
    }

    // If music is not in its clean state
    if (m_currentTrack->getState() != Music::STATE_UNINITIALIZED)
    {
        m_currentTrack->closeAndReset();
    }

    if (m_currentTrack->open(m_filePaths[index], m_audioDevName))
    {
        // If failed to open music at the current index, try the next one
        openTrackAtIndex(index + 1);
    }
    else
    {
        m_currentTrackIndex = index;
    }
}

void Playlist::startPlaying()
{
    // If playlist is empty
    if (m_filePaths.size() < 1)
        return;

    if (m_currentTrack->getState() == m_currentTrack->STATE_UNINITIALIZED)
        openTrackAtIndex(m_currentTrackIndex);
    m_currentTrack->unPause();
}

void Playlist::tickCurrentTrack()
{
    // If playlist is empty
    if (m_filePaths.size() < 1)
        return;

    // If music ended or errored out
    if (m_currentTrack->hasEnded() || m_currentTrack->isInErrorState())
    {
        std::cout << "Current music has ended or errored out, opening next one" << '\n';

        // Play the next music
        ++m_currentTrackIndex;
        // If the music index is valid
        if (m_currentTrackIndex < m_filePaths.size())
            openTrackAtIndex(m_currentTrackIndex);
    }

    // If the music index is valid
    if (m_currentTrackIndex < m_filePaths.size())
    {
        m_currentTrack->tick();
    }
    // End of playlist
    else
    {
        std::cerr << "Cannot tick, playlist ended" << '\n';
    }
}

void Playlist::unpauseCurrentMusic()
{
    m_currentMusic->unPause();
}

void Playlist::pauseCurrentMusic()
{
    m_currentMusic->pause();
}

Playlist::~Playlist()
{
}
