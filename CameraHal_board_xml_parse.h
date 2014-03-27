//camera_xml_config
#ifndef __RK_CAM_XML_CONFIG_H__
#define __RK_CAM_XML_CONFIG_H__
//#include <linux/ioctl>
//#include "calib_xml/calibdb.h"
//#include <isi/isi_iss.h>
//#include <linux/list.h>
#include <utils/Vector.h>
#include <list>
#include <isp_cam_api/calib_xml/calibdb.h>
#include <isi/isi_iss.h>
#include <linux/camsys_head.h>

using namespace android;

#define RK_CAM_FACING_FRONT (1)
#define RK_CAM_FACING_BACK  (0)
#define INVALID_VALUE -1
#define INVALID_GPIO INVALID_VALUE
#define H_ACTIVE (0x01)
#define L_ACTIVE (0x00)

#define RK_RET_SUCCESS  (0)
#define RK_RET_NOFILE   (-1)
#define RK_RET_NULL_POINTER (-2)
#define RK_RET_NOSETUP  (-3)
#define RK_RET_NODEVICE (-4)
#define RK_RET_DEVICEERR (-5)

#define RK_SENSOR_LIB_PATH "/system/lib/hw/libisp_isi_drv_"
#define RK_BOARD_XML_PATH "/etc/cam_board.xml"
#define RK_DEFAULT_MEDIA_PROFILES_XML_PATH "/etc/media_profiles_default.xml"
#define RK_DST_MEDIA_PROFILES_XML_PATH "/data/media_profiles.xml"
#define RK_TMP_MEDIA_PROFILES_XML_PATH "/data/media_profiles_tmp.xml"
#define RK_SENSOR_XML_PATH "/etc/"

typedef enum sensor_output_mode_s{
    OUTPUT_MODE_MIN,
    DVP,
    MIPI_2_LANE,
    MIPI_4_LANE,
    CCIR656,
    OUTPUT_MODE_MAX   
}sensor_output_mode_t;


#define AWB_AUTO_BITPOS                (0)
#define AWB_INCANDESCENT_BITPOS        (1)
#define AWB_FLUORESCENT_BITPOS         (2)
#define AWB_WARM_FLUORESCENT_BITPOS    (3)
#define AWB_DAYLIGHT_BITPOS            (4)
#define AWB_CLOUDY_BITPOS              (5)
#define AWB_TWILIGHT_BITPOS            (6)
#define AWB_SHADE_BITPOS               (7)

#define SENCE_MODE_AUTO_BITPOS          (0)
#define SENCE_MODE_ACTION_BITPOS        (1)
#define SENCE_MODE_PORTRAIT_BITPOS      (2)
#define SENCE_MODE_LANDSCAPE_BITPOS     (3)
#define SENCE_MODE_NIGHT_BITPOS         (4)
#define SENCE_MODE_NIGHT_PORTRAIT_BITPOS    (5)
#define SENCE_MODE_THEATRE_BITPOS       (6)
#define SENCE_MODE_BEACH_BITPOS         (7)
#define SENCE_MODE_SNOW_BITPOS          (8)
#define SENCE_MODE_SUNSET_BITPOS        (9)
#define SENCE_MODE_STEAYPHOTO_BITPOS    (10)
#define SENCE_MODE_PIREWORKS_BITPOS     (11)
#define SENCE_MODE_SPORTS_BITPOS        (12)
#define SENCE_MODE_PARTY_BITPOS         (13)
#define SENCE_MODE_CANDLELIGHT_BITPOS   (14)
#define SENCE_MODE_BARCODE_BITPOS       (15)
#define SENCE_MODE_HDR_BITPOS           (16)

#define EFFECT_NONE_BITPOS      (0)
#define EFFECT_MONO_BITPOS      (1)
#define EFFECT_SOLARIZE_BITPOS  (2)
#define EFFECT_NEGATIVE_BITPOS  (3)
#define EFFECT_SEPIA_BITPOS     (4)
#define EFFECT_POSTERIZE_BITPOS (5)
#define EFFECT_WHITEBOARD_BITPOS    (6)
#define EFFECT_BLACKBOARD_BITPOS    (7)
#define EFFECT_AQUE_BITPOS          (8)

#define ANTI_BANDING_AUTO_BITPOS   (0)
#define ANTI_BANDING_50HZ_BITPOS   (1)
#define ANTI_BANDING_60HZ_BITPOS   (2)
#define ANTI_BANDING_OFF_BITPOS    (3)

#define FLASH_MODE_OFF_BITPOS   (0)
#define FLASH_MODE_ON_BITPOS    (1)
#define FLASH_MODE_TORCH_BITPOS (2)
#define FLASH_MODE_AUTO_BITPOS  (3)
#define FLASH_MODE_RED_EYE_BITPOS   (4)

#define FOCUS_AUTO_BITPOS       (0)
#define FOCUS_INFINITY_BITPOS   (1)
#define FOCUS_MARCO_BITPOS      (2)
#define FOCUS_FIXED_BITPOS      (3)
#define FOCUS_EDOF_BITPOS       (4)
#define FOCUS_CONTINUOUS_VIDEO_BITPOS   (5)
#define FOCUS_CONTINUOUS_PICTURE_BITPOS (6)

struct rk_sensor_info{
    rk_sensor_info():
                mCamDevid(0),
                mSensorI2cAddr(0),
                mMode(OUTPUT_MODE_MIN){};
    ~rk_sensor_info(){};
    
    char mSensorName[CAMSYS_NAME_LEN];
    char mCamsysDevPath[CAMSYS_NAME_LEN];
    char mSensorDriver[16];
    
    //devid
    unsigned int mCamDevid;
    unsigned int mHostDevid;
    

    //i2c
    int mI2cAddrBytes;
    int mSensorI2cAddr;
    int mSensorI2cBusNum;
   
    //clock
    int mSensorI2cRate;
    int mMclkRate;

    //regulator
    camsys_regulator_info_t     mAvdd;         // sensor avdd power regulator name    
    camsys_regulator_info_t     mDovdd;        // sensor dovdd power regulator name    
    camsys_regulator_info_t     mDvdd;         // sensor dvdd power regulator name    "NC" describe no regulator    
    
    //gpio
    camsys_gpio_info_t mSensorGpioReset;
    camsys_gpio_info_t mSensorGpioPwdn;
    camsys_gpio_info_t SensorGpioPwen;

    //powerup_sequence
    unsigned int mSensorGpioFlag;
    int mSensorPowerupSequence;

    //facing: front or back camera
    int mFacing;

    //mipi_2_lane, mipi_4_lane, DVP, CCIR656
    sensor_output_mode_t mMode;

    //mirror and flip 00 01 10 11
    int mMirrorFilp;

    int mOrientation;

    //register info
    unsigned int *mRegbase;
    unsigned int *mI2cbase;

    camsys_extdev_phy_t mPhy;
    

};

struct rk_vcm_info{
    rk_vcm_info():mVcmI2cAddr(0){};
    ~rk_vcm_info(){};
    
    char mVcmName[CAMSYS_NAME_LEN];
    unsigned int mVcmI2cAddr;
    unsigned int mVcmI2cBusNum;
    unsigned int mVcmI2cRate;
    int mI2cAddrBytes;

    camsys_regulator_info_t mVcmVdd;  //"NC" describe no regulator
    
    camsys_gpio_info_t mVcmGpioPwdn;
    camsys_gpio_info_t mVcmGpioPower;

};

struct rk_flash_info{
    rk_flash_info():mFlashI2cAddr(0){};
    ~rk_flash_info();
    
    char mFlashName[CAMSYS_NAME_LEN];
    unsigned int mFlashI2cAddr;
    unsigned int mFlashI2cBusNum;
    unsigned int mFlashI2cRate;
    
    int mI2cAddrBytes;
    camsys_regulator_info_t mFlashVdd; //"NC" describe no regulator
    
    camsys_gpio_info_t mFlashGpioPwdn;
    camsys_gpio_info_t mFlashGpioPower;
};

struct rk_cam_hardware_info{
    rk_cam_hardware_info(){};
    ~rk_cam_hardware_info(){};
    
    rk_sensor_info mSensorInfo;
    rk_vcm_info mVcmInfo;
    rk_flash_info mFlashInfo;
};

struct rk_white_balance_config{
    rk_white_balance_config():mAwbSupport(0),mDefault(0){};
    ~rk_white_balance_config(){};
    
    unsigned int mAwbSupport;
    unsigned int mDefault;
};

struct rk_sence_config{
    rk_sence_config():mSenceSupport(0),mDefault(0){};
    ~rk_sence_config(){};
    
    unsigned int mSenceSupport;
    unsigned int mDefault;
};

struct rk_effect_config{
    rk_effect_config():mEffectSupport(0),mDefault(0){};
    ~rk_effect_config(){};
    
    unsigned int mEffectSupport;
    unsigned int mDefault;
};   

struct rk_anti_banding_config{
    rk_anti_banding_config():mAntiBandingSupport(0),mDefault(0){};
    ~rk_anti_banding_config(){};
    
    unsigned int mAntiBandingSupport;
    unsigned int mDefault;
};


struct rk_flash_config{
    rk_flash_config():mFlashSupport(0),mDefault(0){};
    ~rk_flash_config(){};
    
    unsigned int mFlashSupport;
    unsigned int mDefault;
};

struct rk_focus_config{
    rk_focus_config():mFocusSupport(0),mDefault(0){};
    ~rk_focus_config(){};

    unsigned int mFocusSupport;
    unsigned int mDefault;
};

struct rk_DV_info{
    rk_DV_info()
            :mWidth(0),
            mHeight(0),
            mFps(0),
            mIsSupport(0){};
            
    ~rk_DV_info(){};
    
    char mName[CAMSYS_NAME_LEN];
    int mWidth;
    int mHeight;
    int mFps;
    int mIsSupport;
    uint32_t mResolution;
    int mAddMask;
};


struct rk_camera_softinfo_config{
    rk_camera_softinfo_config()
                    :mZSLConfig(0),
                    mContinue_snapshot_config(0),
                    mPreviewWidth(800),
                    mPreviewHeight(600),
                    mHDRConfig(0){};
    ~rk_camera_softinfo_config(){};               
                    
                    
    rk_white_balance_config mAwbConfig;
    rk_sence_config mSenceConfig;
    rk_effect_config mEffectConfig;
    rk_anti_banding_config mAntiBandingConfig;
    rk_focus_config mFocusConfig;
    rk_flash_config mFlashConfig;
    
    int mZSLConfig;
    int mContinue_snapshot_config;
    int mPreviewWidth;
    int mPreviewHeight;
    int mHDRConfig;
    
    Vector<rk_DV_info*> mDV_vector;
};

struct camsys_load_sensor_info{
    camsys_load_sensor_info(){};
    ~camsys_load_sensor_info(){};

    CalibDb calidb;           
    IsiCamDrvConfig_t *pCamDrvConfig;
    void *mhSensorLib;
    int mCamsysFd;
    sensor_i2c_info_t* mpI2cInfo;
    char mSensorLibName[50];
    char mSensorXmlFile[50];
};

struct rk_cam_total_info{
    rk_cam_total_info():mDeviceIndex(-1),mIsConnect(0){};
    ~rk_cam_total_info(){};
    rk_cam_hardware_info mHardInfo;
    rk_camera_softinfo_config mSoftInfo;
    camsys_load_sensor_info mLoadSensorInfo;
    int mDeviceIndex;
    int mIsConnect;
};


class camera_board_profiles{
public:

    struct xml_DEV_name_s{
	    int camid;
	    char camera_name[CAMSYS_NAME_LEN];
	    int index;
	    int facing;
    };

    struct xml_fp_pos_s{          
    	int camid;
    	long camid_start;
    	long camid_end;
    };

    struct xml_video_element_s{                
    	int n_cameraId;
    	char str_quality[CAMSYS_NAME_LEN];
    	int n_width;
    	int n_height;
    	int n_frameRate;
    	int isAddMark;
    };

    
    static camera_board_profiles* getInstance();
    static camera_board_profiles*  createInstance();
    static void ParserSensorInfo(const char *name, const char **atts, void *userData);
    static void ParserVCMInfo(const char *name, const char **atts, void *userData);
    static void ParserFlashInfo(const char *name, const char **atts, void *userData);
    static void ParserAwbConfig(const char *name, const char **atts, void *userData);
    static void ParserSenceConfig(const char *name, const char **atts, void *userData);
    static void ParserEffectConfig(const char *name, const char **atts, void *userData);
    static void ParserFocusConfig(const char *name, const char **atts, void *userData);
    static void ParserAntiBandingConfig(const char *name, const char **atts, void *userData);
    static void ParserDVConfig(const char *name, const char **atts, void *userData);
    static void StartElementHandler(void *userData, const char *name, const char **atts);
    static bool LoadALLCalibrationData(camera_board_profiles* profiles);
    static void OpenAndRegistALLSensor(camera_board_profiles* profiles);
    static void OpenAndRegistOneSensor(rk_cam_total_info *pCamInfo);
    static int RegisterSensorDevice(rk_cam_total_info* pCamInfo);
    static int ProduceNewXml(camera_board_profiles* profiles);
    static int CheckSensorSupportDV(rk_cam_total_info* pCamInfo);
    static int WriteDevNameTOXML(camera_board_profiles* profiles, char *SrcFile, char* DstFile);
    static int ReadDevNameFromXML(FILE* fp, xml_DEV_name_s* video_name);
    static int XMLFseekCamIDPos(FILE* fp, xml_fp_pos_s* fp_pos);
    static int FindResolution(camera_board_profiles* profiles, xml_video_element_s* find_element);
    static int ModifyMediaProfileXML( camera_board_profiles* profiles, char* src_xml_file, char* dst_xml_file);
    static int LoadSensor(camera_board_profiles* profiles);
    static int BoardFileHaveDev(camera_board_profiles* profiles, xml_DEV_name_s* media_xml_device);
    static void AddConnectSensorToVector(camera_board_profiles* profiles);


    Vector<rk_cam_total_info*> mDevieVector;
    Vector<rk_cam_total_info*> mDevideConnectVector;

    rk_cam_total_info *mCurDevice;

    xml_DEV_name_s mXmlDevInfo[2];

};


#endif
