//
// Created by Michal.Kawski on 27.01.2026.
//

#include "Core/MetronomeService.h"
#include <chrono>

namespace Core {

    MetronomeService::MetronomeService(int intervalMs) : m_intervalMs(intervalMs), m_running(false)
    {

    }

    MetronomeService::~MetronomeService() {
        Stop();
    }

    void MetronomeService::AddCallback(std::function<void(float)> updateFunc)
    {
        m_updateCallbacks.emplace_back(updateFunc);
    }

    void MetronomeService::Start()
    {
        if (m_running) return;
        m_running = true;
        m_worker = std::thread([this]() {
            auto lastTime = std::chrono::steady_clock::now();
            while (m_running) {
                auto now = std::chrono::steady_clock::now();
                std::chrono::duration<float, std::milli> delta = now - lastTime;
                lastTime = now;

                // Call update callback
                for (auto &callback : m_updateCallbacks) {
                    callback(delta.count());
                }

                // Sleep for the desired interval
                std::this_thread::sleep_for(std::chrono::milliseconds(m_intervalMs));
            }
        });
    }

    void MetronomeService::Stop()
    {
        m_running = false;
        if (m_worker.joinable()) m_worker.join();
    }

} // Core