#pragma once
#include <string>
#include <chrono>

namespace Util {
    constexpr float M_PI{ 3.14159265f };

    template<typename T>
    const T& Clamp(const T& value, const T& min, const T& max) {
        if (value < min) {
            return min;
        }
        else if (value > max) {
            return max;
        }
        else {
            return value;
        }
    }

    namespace Convert {
        inline constexpr float ToRadian(float fDegrees) { return fDegrees * M_PI / 180.0f; }
        inline constexpr float ToDegree(float fRadians) { return fRadians * 180.0f / M_PI; }
    }

    class Timer {
    public: // ��`
        using nanoseconds = std::chrono::nanoseconds;
        using microseconds = std::chrono::microseconds;
        using milliseconds = std::chrono::milliseconds;
        using seconds = std::chrono::seconds;
        using minutes = std::chrono::minutes;
        using hours = std::chrono::hours;

    public: // �ÓI�֐�
        /// <summary>
        /// <para>Windows���N�����Ă���̌o�ߎ��Ԃ��~���b�P�ʂł���킵���l��Ԃ��B</para>
        /// <para>���������擾����킯�ł͂Ȃ����A���̊֐��̑��݈Ӌ`�͎��Ԍv���ɂ���B</para>
        /// <para>TimeUnit��std::chrono::duration�̕ʖ��ɂ���[���ԊԊu��\���^]</para>
        /// <para>�݂̂��g�p�ł���B</para>
        /// </summary>
        /// <typeparam name="TimeUnit"></typeparam>
        /// <returns></returns>
        template<class TimeUnit>
        static int32_t GetNowCount(void);

    public: // �֐�
        void Start(float_t endTime = 1.0f);

        // getter
        const bool GetIsEnd(void);

    private: // �ϐ�
        int32_t startTime_{ 0 }; // �v���J�n����
        float_t endTime_{ 0.0f }; // ���B�ڕW����

        bool isEnd_{ false }; // endTime_ < elapsedTime_ = true
    };

    namespace Ease {
        float EaseInSine(float t);
        float EaseInSine(float start, float end, float t);
        float EaseInCubic(float t);
        float EaseInCubic(float start, float end, float t);
        float EaseInQuint(float t);
        float EaseInQuint(float start, float end, float t);
        float EaseInCirc(float t);
        float EaseInCirc(float start, float end, float t);
        float EaseInElastic(float t);
        float EaseInElastic(float start, float end, float t);

        float EaseInOutSine(float t);
        float EaseInOutSine(float start, float end, float t);
    }

    namespace expt {

    }
}