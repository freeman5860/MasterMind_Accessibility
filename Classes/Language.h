//
//  Language.h
//  Mole Guess
//
//  Created by Freeman on 2017/1/14.
//
//

#ifndef Language_h
#define Language_h

#include "cocos2d.h"

using namespace cocos2d;

//return type:const char*
#define LocalizedCStringByKey(key) Language::getStringByKey(key)

class Language{
    
public:
    
    static const char* getStringByKey(const char * key){
        
        //获取当前系统环境语言类型
        ccLanguageType languageType = CCApplication::sharedApplication()->getCurrentLanguage();
        
        //字典
        CCDictionary *pDic;
        
        if(kLanguageChinese == languageType){
            //依据语言选择不同的属性表
            pDic = CCDictionary::createWithContentsOfFileThreadSafe("language/zh.plist");
        }else{
            pDic = CCDictionary::createWithContentsOfFileThreadSafe("language/en.plist");
        }
        
        std::string keyStr = key;
        
        //返回key相应的value
        return (pDic -> valueForKey(keyStr))->getCString();
    }
    
};

#endif /* Language_h */
