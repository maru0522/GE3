#pragma once
#include <string>

namespace Util {
    namespace Convert {
        //----------//
        /* ������ϊ� */
        //----------//

        // char* -> string
        std::string CharToString(const char* cstr);
        // char* -> wstring(unicode)
        std::wstring CharToWString(const char* cstr);

        // wchar_t*(unicode) -> string 
        std::string WCharToString(const wchar_t* wcstr);
        // wchar_t*(unicode) -> wstring(unicode)
        std::wstring WCharToWString(const wchar_t* wcstr);

        // string -> wstring(unicode)
        std::wstring StringToWString(const std::string str);
        // wstring(unicode) -> string
        std::string WstringToString(const std::wstring wstr);
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