#pragma once
#include <string>

namespace Util {
    namespace Convert {
        //----------//
        /* ������ϊ� */
        //----------//

    }

    class Timer {
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
}