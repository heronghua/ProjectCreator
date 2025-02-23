/*************************************************************************
	 File Name: src/AndroidProjectCreator.h
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb 16 21:26:09 2025
 ************************************************************************/

#ifndef ANDROID_PROJECT_CREATOR
#define ANDROID_PROJECT_CREATOR 1

#include <iostream>
#include "IProjectCreator.h"
#include "IHelper.h"
#include <filesystem>


#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include <incbin.h>


using namespace std;

/* Usage: INCBIN(<<LABLE>>, <<FILE>>)
 *
 * Symbols defined by INCBIN 
 * ------------------------------------------ 
 *  const unsigned char        g_asset_data[]  // g_<<LABLE>>_data 
 *  const unsigned char* const g_asset_end;    // g_<<LABEL>>_end 
 *  const unsinged int         g_asset_size;   // g_<<LABEL>>_size 
 */
INCBIN(xml_string, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/strings.template");
INCBIN(icon_hdpi, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/ic_launcher_hdpi.png");
INCBIN(icon_ldpi, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/ic_launcher_ldpi.png");
INCBIN(icon_mdpi, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/ic_launcher_mdpi.png");
INCBIN(icon_xhdpi, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/ic_launcher_xhdpi.png");
INCBIN(manifest, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/AndroidManifest.template");
INCBIN(activity, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/java_file.template");
INCBIN(proguard, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/proguard-project.txt");


class AndroidProjectCreator : public IProjectCreator
{
    public:
        void createProject(string& projectName,string& packageName) override
        {
          map<string,string> replaceMap;
          replaceMap["PROJECT_NAME"] = projectName;
          replaceMap["PACKAGE"] = packageName;
          ThreadPool pool(10); 
          auto sharedMap=std::make_shared<std::map<string,string>>(replaceMap);

          string xmlStringContent = string(g_xml_string_data, g_xml_string_data + g_xml_string_size);
          string destFilePath = projectName + filesystem::path::preferred_separator + "res" + filesystem::path::preferred_separator + "values" + filesystem::path::preferred_separator + "strings.xml";
          pool.enqueue(replaceKeyWithValue,xmlStringContent, sharedMap, destFilePath);

          string hdpiStringContent = string(g_icon_hdpi_data,g_icon_hdpi_data + g_icon_hdpi_size);
          string hdpiFilePath = projectName + filesystem::path::preferred_separator + "res" + filesystem::path::preferred_separator + "drawable-hdpi" + filesystem::path::preferred_separator + "ic_launcher.png";
          pool.enqueue(replaceKeyWithValue,hdpiStringContent, nullptr, hdpiFilePath);

          string ldpiStringContent = string(g_icon_ldpi_data,g_icon_ldpi_data + g_icon_ldpi_size);
          string ldpiFilePath = projectName + filesystem::path::preferred_separator + "res" + filesystem::path::preferred_separator + "drawable-ldpi" + filesystem::path::preferred_separator + "ic_launcher.png";
          pool.enqueue(replaceKeyWithValue,ldpiStringContent, nullptr, ldpiFilePath);

          string mdpiStringContent = string(g_icon_mdpi_data,g_icon_mdpi_data + g_icon_mdpi_size);
          string mdpiFilePath = projectName + filesystem::path::preferred_separator + "res" + filesystem::path::preferred_separator + "drawable-mdpi" + filesystem::path::preferred_separator + "ic_launcher.png";
          pool.enqueue(replaceKeyWithValue,mdpiStringContent, nullptr, mdpiFilePath);

          string xhdpiStringContent = string(g_icon_xhdpi_data,g_icon_xhdpi_data + g_icon_xhdpi_size);
          string xhdpiFilePath = projectName + filesystem::path::preferred_separator + "res" + filesystem::path::preferred_separator + "drawable-xhdpi" + filesystem::path::preferred_separator + "ic_launcher.png";
          pool.enqueue(replaceKeyWithValue,xhdpiStringContent, nullptr, xhdpiFilePath);

          string manifestStringContent = string(g_manifest_data,g_manifest_data + g_manifest_size);
          string manifestFilePath = projectName + filesystem::path::preferred_separator + "AndroidManifest.xml";
          pool.enqueue(replaceKeyWithValue,manifestStringContent, sharedMap, manifestFilePath);

          string activityStringContent = string(g_activity_data,g_activity_data + g_activity_size);
          string packageNameToPath=packageName;
            size_t pos = packageNameToPath.find(".");
            while (pos != string::npos) {
                //TODO use perferred_separator
                packageNameToPath.replace(pos, 1, "/");
                pos = packageNameToPath.find(".", pos + 2);
            }
          string activityFilePath = projectName + filesystem::path::preferred_separator + packageNameToPath + filesystem::path::preferred_separator + "MainActivity.java";
          pool.enqueue(replaceKeyWithValue,activityStringContent, sharedMap, activityFilePath);

          string proguardStringContent = string(g_proguard_data,g_proguard_data + g_proguard_size);
          string proguardFilePath = projectName + filesystem::path::preferred_separator + "proguard-project.txt";
          pool.enqueue(replaceKeyWithValue,proguardStringContent, nullptr, proguardFilePath);


        }

};

#endif /* ifndef ANDROID_PROJECT_CREATOR */
