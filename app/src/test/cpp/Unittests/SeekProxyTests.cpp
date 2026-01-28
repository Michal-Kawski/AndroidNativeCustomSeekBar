//
// Created by Michal.Kawski on 28.01.2026.
//

#include <Core/SeekProxy.h>

#include "../Mocks/Core/MockMediaController.h"

#include <gtest/gtest.h>
#include <memory>

using ::testing::Return;
using ::testing::_;

static constexpr int64_t DURATION_MS = 1000;

class SeekProxyTest : public ::testing::Test
{
public:
    void SetUp() override {
        m_pSeekProxy = std::make_unique<Core::SeekProxy>(m_mockMediaController, DURATION_MS);
    }

    void TearDown() override {
        m_pSeekProxy.reset();
    }

protected:
    MockMediaController m_mockMediaController;
    std::unique_ptr<Core::SeekProxy> m_pSeekProxy;
};

TEST_F(SeekProxyTest, OnDoubleTapTest) {
    EXPECT_CALL(m_mockMediaController, SeekTo(DURATION_MS)).Times(1);
    m_pSeekProxy->OnDoubleTap(DURATION_MS + 100);
}

TEST_F(SeekProxyTest, SeekToNormalizedTest) {
    EXPECT_CALL(m_mockMediaController, SeekTo(DURATION_MS)).Times(1);
    m_pSeekProxy->SeekToNormalized(12346.0f);
}

TEST_F(SeekProxyTest, SeekToTimeMsTest) {
    EXPECT_CALL(m_mockMediaController, SeekTo(500)).Times(1);
    m_pSeekProxy->SeekToTimeMs(500);
}

TEST_F(SeekProxyTest, TimeToNormalizedTest) {
    EXPECT_EQ(m_pSeekProxy->TimeToNormalized(1000), 1.0f);
    EXPECT_EQ(m_pSeekProxy->TimeToNormalized(0), 0.0f);
    EXPECT_EQ(m_pSeekProxy->TimeToNormalized(static_cast<float>(DURATION_MS)/2), 0.5f);
}

TEST_F(SeekProxyTest, NormalizedToTimeTest) {
    EXPECT_EQ(m_pSeekProxy->NormalizedToTime(1.0f), DURATION_MS);
    EXPECT_EQ(m_pSeekProxy->NormalizedToTime(0.0f), 0LL);
    EXPECT_EQ(m_pSeekProxy->NormalizedToTime(0.5f), static_cast<float>(DURATION_MS)/2.0f);
}
