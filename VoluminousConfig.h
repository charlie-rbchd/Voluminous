#ifndef VoluminousConfig_H
#define VoluminousConfig_H

// NB: If you change anything in here, make sure to also change
// the values in the xml file located in the WwisePlugin directory.
namespace VoluminousConfig
{
    enum { companyId = 232, pluginId = 2018 };

    static short nextParameterId = 0;
    #define AUTO_INCREMENT (nextParameterId++)

    static const struct
    {
        short id;

        const wchar_t* name;
        const wchar_t* displayName;

        float minValue;
        float maxValue;
        float defaultValue;
    }
    parameters[] =
    {
        { AUTO_INCREMENT, L"gain", L"Gain", 0.0f, 1.0f, 0.5f }
    };
}

#endif // VoluminousConfig_H
