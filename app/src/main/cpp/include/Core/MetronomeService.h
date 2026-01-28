//
// Created by Michal.Kawski on 27.01.2026.
//

#ifndef CUSTOMSEEKBAR_METRONOMESERVICE_H
#define CUSTOMSEEKBAR_METRONOMESERVICE_H


#include <functional>
#include <thread>
#include <atomic>

namespace Core {

    class MetronomeService final {
    public:
        MetronomeService(int intervalMs);
        ~MetronomeService();

        void AddCallback(std::function<void(float)> updateFunc);
        void Start();
        void Stop();

    private:
        std::vector<std::function<void(float)>> m_updateCallbacks;
        int m_intervalMs = 100;
        std::atomic<bool> m_running;
        std::thread m_worker;
    };

} // Core

#endif //CUSTOMSEEKBAR_METRONOMESERVICE_H
