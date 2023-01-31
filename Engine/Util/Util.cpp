#include "Util.h"
#include <chrono>
#include <cmath>

using namespace std::chrono;

template<class TimeUnit>
inline int32_t Util::Timer::GetNowCount(void)
{
    // template‚ÌŒ^‚Í[ŠÔŠÔŠu‚ğ‚ğ•\‚·Œ^]‚Å‚È‚¯‚ê‚Î‚È‚ç‚È‚¢B
    // ref: https://cpprefjp.github.io/reference/chrono/duration_aliases.html

    return (int32_t)duration_cast<TimeUnit>(steady_clock::now().time_since_epoch()).count();
}

void Util::Timer::Start(float_t endTime)
{
    startTime_ = GetNowCount<milliseconds>();
}

const bool Util::Timer::GetIsEnd(void)
{
    float_t elapsedTime = (GetNowCount<milliseconds>() - startTime_) / 1000.0f;
    return endTime_ < elapsedTime;
}

float Util::Ease::EaseInSine(float t)
{
    return 1.f - std::cosf((t * M_PI) / 2.f);
}

float Util::Ease::EaseInSine(float start, float end, float t)
{
    return start + (end - start) * (1.f - std::cosf(t * (M_PI / 2.f)));
}

float Util::Ease::EaseInCubic(float t)
{
    return t * t * t;
}

float Util::Ease::EaseInCubic(float start, float end, float t)
{
    return start + (end - start) * (t * t * t);
}

float Util::Ease::EaseInQuint(float t)
{
    return t * t * t * t * t;
}

float Util::Ease::EaseInQuint(float start, float end, float t)
{
    return start + (end - start) * (t * t * t * t * t);
}

float Util::Ease::EaseInCirc(float t)
{
    return 1.f - std::sqrtf(1.f - t * t);
}

float Util::Ease::EaseInCirc(float start, float end, float t)
{
    float time{ 1.f - std::sqrtf(1.f - t * t) };
    return start * (1.f - time) + end * time;
}

float Util::Ease::EaseInElastic(float t)
{
    const float c4 = (2.f * M_PI) / 3.f;
    if (t == 0.f) {
        return 0.f;
    }
    else if (t == 1) {
        return 1.f;
    }
    else {
        return -std::powf(2.f, 10.f * t - 10.f) * std::sinf((t * 10.f - 10.75f) * c4);
    }
}

float Util::Ease::EaseInElastic(float start, float end, float t)
{
    const float c4 = (2.f * M_PI) / 3.f;
    if (t == 0.f) return start;
    else if (t == 1.f) return end;
    else return -std::powf(2.f, 10.f * t - 10.f) * std::sinf((t * 10.f - 10.75f) * c4);
}

float Util::Ease::EaseInOutSine(float t)
{
    return -(std::cosf(M_PI * t) - 1.f) / 2.f;
}

float Util::Ease::EaseInOutSine(float start, float end, float t)
{
    float time = -(std::cosf(M_PI * t) - 1.f) / 2.f;
    return start * (1.f - time) + end * time;
}
