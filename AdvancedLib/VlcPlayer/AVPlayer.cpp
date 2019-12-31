#include "stdafx.h"
#include "AVPlayer.h"
#include <cmath>
#include <C++/FoundationLib/StringExtLib/StringConverter.h>

CAVPlayer::CAVPlayer(void) :
m_pVLC_Inst(NULL),
m_vlc_media(NULL),
m_pVLC_Player(NULL),
m_hWnd(NULL),
m_pfnPlaying(NULL),
m_pfnPosChanged(NULL),
m_pfnEndReached(NULL),
m_retryTimes(PLAY_FAILURE_RETRY_TIMES)
{
}

CAVPlayer::~CAVPlayer(void)
{
    Release();
}

void CAVPlayer::Init()
{
    m_errMsg = "";

    Release();

    if (! m_pVLC_Inst)
    {
		const char* const vlc_args[] = {
	   "-I", "dummy", /* Don't use any interface */
// 	   "--sub-filter=logo{file=D:\\旧数据\\G\\图片\\2014-09-15_12-23-56_741.jpg}",
	    //"--sub-filter=logo{file=c:\\mediaport.png}:rss{urls=http://www.bbc.co.uk/persian/index.xml,length=120,size=23,title=0,speed=300000,x=-10,y=-30,position=8}",
        //"--sub-filter=logo{file=dummy}",
	   //"--no-rss-images",
//        "--rotation-angle=30",  // 实例创建失败，即使写成90也不行
//       "--video-filter=transform",  // 逆时针旋转90度（好使）
//       "--transform-type=",   // 值可以是 90, 180, 270, hfilp, vfilp

        // 设置了 marq 就不要设置 logo；
        // 设置了 logo marq 自动不显示（一闪就没了）
	   "--sub-filter=marq",    // 允许向画面中添加文字

// 	   "--sub-filter=logo",// 允许显示 logo

        "--verbose", "0",
	   //"--verbose-objects=+filter",
// 	   "-vvv",
	   //"--sout=#duplicate{dst=std{access=mmsh,mux=asfh,dst=0.0.0.0:8080},dst=display}",
	   //"--ignore-config",
	   //"--loop",
	   //"--repeat",
	   //"-R",
	   "--no-video-title-show",
	   //"--network-caching 20000",
	   //":mmsh-caching=20000",
		};

		int vlc_argc = sizeof(vlc_args) / sizeof(*vlc_args);
		m_pVLC_Inst = libvlc_new(vlc_argc, vlc_args);
//		m_pVLC_Inst = libvlc_new(0, NULL);
	}
}

void CAVPlayer::Release()
{
    Stop();

    if (m_vlc_media)
    {
        libvlc_media_release(m_vlc_media);
        m_vlc_media = NULL;
    }

    if (m_pVLC_Inst)
    {
        libvlc_release (m_pVLC_Inst);
        m_pVLC_Inst   = NULL;
    }
}

bool CAVPlayer::Play(const std::string &strPath, int type)
{
	m_errMsg = "";
    int retryTimes = m_retryTimes;

    Init();

    if(strPath.empty() || ! m_pVLC_Inst)
    {
		m_errMsg = "传入参数为空，或播放器实例创建失败！";
        return false;
    }

    Stop();

    bool bRet = false;

	switch (type)
	{
	case 0:
		m_vlc_media = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str());
		break;
	case 1:
		m_vlc_media = libvlc_media_new_location(m_pVLC_Inst, strPath.c_str());
// 		m = libvlc_media_new_location(m_pVLC_Inst, "screen://");  // 显示屏幕内容居然也可以
		break;
	default:
		m_vlc_media = libvlc_media_new_path(m_pVLC_Inst, strPath.c_str());
		break;
	}

    if (!m_vlc_media)
    {
		m_errMsg = "媒体文件加载失败！";
		return false;
    }

	// 有人说这么调用的时候，必须前面用冒号，而不是短划线或双短划线
	libvlc_media_add_option(m_vlc_media, ":rtsp-tcp");
// 	libvlc_media_add_option(m_vlc_media, ":ipv4-timeout=3000");  // 这个是连接超时
//  libvlc_media_add_option(m_vlc_media, ":rtp-timeout=5000");  // 这个是 rtp 视频流超时
// 	libvlc_media_add_option(m_vlc_media, ":rtsp-session-timeout=10000");   // 用于 rtsp 协议文本中设置超时
	libvlc_media_add_option(m_vlc_media, ":network-caching=1000");
	libvlc_media_add_option(m_vlc_media, ":rtsp-frame-buffer-size=0.5");
// 	libvlc_media_add_option(m_vlc_media, ":global-key-toggle-fullscreen={f}");

	//libvlc_media_add_option(m_vlc_media, "--avcodec-threads=124");
	//libvlc_media_add_option(m_vlc_media, "--ignore-config");
// 	libvlc_media_add_option(m_vlc_media, "--network-caching=1500000");
// 	libvlc_media_add_option(m_vlc_media, "--rtsp-frame-buffer-size=2000000");
// 	libvlc_media_add_option(m_vlc_media, "--rtsp-tcp");
	//libvlc_media_add_option(m_vlc_media, "--advanced");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-toggle-fullscreen=f");
// 	//libvlc_media_add_option(m_vlc_media, "--key-toggle-fullscreen=f");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-leave-fullscreen={ESC}");
// 	//libvlc_media_add_option(m_vlc_media, "--key-leave-fullscreen={ESC}");
// 	libvlc_media_add_option(m_vlc_media, "--global-key-play-pause={SPACE}");
// 	//libvlc_media_add_option(m_vlc_media, "--key-play-pause={SPACE}");

	if (m_pVLC_Player = libvlc_media_player_new_from_media(m_vlc_media))
    {
        /*
			enum libvlc_video_marquee_option_t
			Marq options definition.

			Enumerator
			libvlc_marquee_Enable   0
			libvlc_marquee_Text     1
			libvlc_marquee_Color    2    string argument
			libvlc_marquee_Opacity  3
			libvlc_marquee_Position 4
			libvlc_marquee_Refresh  5
			libvlc_marquee_Size     6
			libvlc_marquee_Timeout  7
			libvlc_marquee_X        8
			libvlc_marquee_Y        9
        */

// 		SetWatermarkString(L"哈哈fdsf");  // 设置 文字水印 好使！！！
// 		SetWatermarkLogo(L"D:\\01.png");  // 设置 logo 不好使

		libvlc_media_player_set_hwnd(m_pVLC_Player, m_hWnd);
        int ret=libvlc_media_player_play(m_pVLC_Player);
        while (ret != 0)
        {
            if (retryTimes == 0)
            {
				m_errMsg = libvlc_errmsg();
                return false;
            }

            retryTimes--;
            ret = libvlc_media_player_play(m_pVLC_Player);
        }

        // 事件管理
        libvlc_event_manager_t *vlc_evt_man = libvlc_media_player_event_manager(m_pVLC_Player);
        libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPlaying, ::OnVLC_Event, this);
        libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerPositionChanged, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEndReached, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaStateChanged, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_MediaPlayerEncounteredError, ::OnVLC_Event, this);
		libvlc_event_attach(vlc_evt_man, libvlc_VlmMediaInstanceStatusError, ::OnVLC_Event, this);
        bRet = true;
    }

//     libvlc_media_release(m_vlc_media);

    return bRet;
}

bool CAVPlayer::PlayUrl(const std::string& url)  // 播放地址为url的视频流
{
	return Play(url, 1);
}


void CAVPlayer::Stop()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_stop (m_pVLC_Player);      /* Stop playing */    
        libvlc_media_player_release (m_pVLC_Player);   /* Free the media_player */
        m_pVLC_Player = NULL;
    }
}

void CAVPlayer::Play()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_play(m_pVLC_Player);
    }
}

void CAVPlayer::Pause()
{
    if (m_pVLC_Player)
    {
        libvlc_media_player_pause(m_pVLC_Player);
    }
}

void CAVPlayer::Volume(int iVol)
{
    if (iVol < 0)
    {
        return;
    }

    if (m_pVLC_Player)
    {
        libvlc_audio_set_volume(m_pVLC_Player,int(iVol * 1.3)); // 如果放到100，感觉比迅雷的100少了30，所以这里用1.3倍音量
    }
}

void CAVPlayer::VolumeIncrease()
{
    if (m_pVLC_Player)
    {
        int iVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)ceil(iVol * 1.1));
    }
}

void CAVPlayer::VolumeReduce()
{
    if (m_pVLC_Player)
    {
        int iVol = libvlc_audio_get_volume(m_pVLC_Player);
        Volume((int)floor(iVol * 0.9));
    }
}

int CAVPlayer::GetPos()
{   
    if (m_pVLC_Player)
    {
        return (int)(1000 * libvlc_media_player_get_position(m_pVLC_Player));
    }

    return 0;
}

void CAVPlayer::SeekTo(int iPos)
{
    if (iPos < 0 || iPos > 1000)
    {
        return;
    }

    if (m_pVLC_Player)
    {
        libvlc_media_player_set_position(m_pVLC_Player, iPos/(float)1000.0);
    }
}

void CAVPlayer::SeekForward()
{
    //int iPos = GetPos();
    //SeekTo((int)ceil(iPos * 1.1));

    // 一次快退5秒
    if (m_pVLC_Player)
    {
        libvlc_time_t i_time = libvlc_media_player_get_time(m_pVLC_Player) + 5000;

        if (i_time > GetTotalTime())
        {
            i_time = GetTotalTime();
        }

        libvlc_media_player_set_time(m_pVLC_Player, i_time);
    }
}

void CAVPlayer::SeekBackward()
{
    //int iPos = GetPos();
    //SeekTo((int)floor(iPos * 0.9));

    if (m_pVLC_Player)
    {
        libvlc_time_t i_time = libvlc_media_player_get_time(m_pVLC_Player) - 5000;

        if (i_time < 0)
        {
            i_time = 0;
        }

        libvlc_media_player_set_time(m_pVLC_Player, i_time);
    }
}

void CAVPlayer::SetHWND( HWND hwnd )
{
    if (::IsWindow(hwnd))
    {
        m_hWnd = hwnd;
    }
}

HWND CAVPlayer::GetHWND()
{
    return m_hWnd;
}


void CAVPlayer::SetFullScreen(bool full)
{
	libvlc_set_fullscreen(m_pVLC_Player, full);
	int iRet = libvlc_get_fullscreen(m_pVLC_Player);
}

bool CAVPlayer::IsOpen()
{
    return NULL != m_pVLC_Player;
}

bool CAVPlayer::IsPlaying()
{
    if (m_pVLC_Player)
    {
		return (1 == libvlc_media_player_is_playing(m_pVLC_Player));
	}

    return false;
}

bool CAVPlayer::IsPlayingError()
{
    libvlc_state_t status = libvlc_media_get_state(m_vlc_media);
    if (status == libvlc_Error)
        return true;

    return false;
}

__int64 CAVPlayer::GetTotalTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_length(m_pVLC_Player);
    }

    return 0;
}

__int64 CAVPlayer::GetTime()
{
    if (m_pVLC_Player)
    {
        return libvlc_media_player_get_time(m_pVLC_Player);
    }

    return 0;
}

int CAVPlayer::GetVolume()
{
    if (m_pVLC_Player)
    {
        return libvlc_audio_get_volume(m_pVLC_Player);
    }

    return 0;
}

void CAVPlayer::SetWatermarkString(CString str, int fontSize, int x, int y, COLORREF color, int transparent, int timeout)
{
// 	libvlc_video_set_logo_string(m_pVLC_Player, libvlc_logo_file, "c:\\audio.png");//Logo 文件名

	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Enable, 1);
#ifdef _UNICODE
    std::string disp = CStringConverter::UnicodeToUtf8(str);
#else
    std::string disp = (LPTSTR)(LPCSTR)str;
#endif
	libvlc_video_set_marquee_string(m_pVLC_Player, libvlc_marquee_Text, disp.c_str());
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Color, color);
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Position, 0);
	//{0 (居中), 1 (左), 2 (右), 4 (上), 8 (下), 5 (左上), 6 (右上), 9 (左下), 10 (右下)} 
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Opacity, transparent);
	//0 = 透明，255 = 完全不透明。
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_X, x); //从屏幕左边缘开始的 X 偏移。
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Y, y);//  从屏幕顶部向下的 Y 偏移。
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Timeout, timeout);
	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Size, fontSize);
// 	libvlc_video_set_marquee_int(m_pVLC_Player, libvlc_marquee_Refresh, 10);
}

void CAVPlayer::SetWatermarkLogo(CString logoPath, int x /*= 0*/, int y /*= 0*/, int transparent /*= 0*/)
{
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_enable, 1);//设置允许添加logo
	libvlc_video_set_logo_string(m_pVLC_Player, libvlc_logo_file, "D:\\01.png,10,10;");//Logo 文件名
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_x, 100);  //logo的 X 坐标。
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_y, 100); // logo的 Y 坐标。
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_delay, 0);//标志的间隔图像时间为毫秒,图像显示间隔时间 0 - 60000 毫秒。
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_repeat, 0); // 标志logo的循环,  标志动画的循环数量。-1 = 继续, 0 = 关闭
	libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_opacity, 122); // logo 透明度 (数值介于 0(完全透明) 与 255(完全不透明)
	//libvlc_video_set_logo_int(m_pVLC_Player, libvlc_logo_position, 6);//1 (左), 2 (右), 4 (顶部), 8 (底部), 5 (左上), 6 (右上), 9 (左下), 10 (右下),您也可以混合使用这些值，例如 6=4+2表示右上)。
}

void CAVPlayer::SetCallbackPlaying( pfnCallback pfn )
{
    m_pfnPlaying = pfn;
}

void CAVPlayer::SetCallbackPosChanged( pfnCallback pfn )
{
    m_pfnPosChanged = pfn;
}

void CAVPlayer::SetCallbackEndReached( pfnCallback pfn )
{
    m_pfnEndReached = pfn;
}

void OnVLC_Event( const libvlc_event_t *event, void *data )
{
    CAVPlayer *pAVPlayer = (CAVPlayer *) data;
    pfnCallback pfn = NULL;

    if (! pAVPlayer)
    {
        return;
    }

    switch(event->type)
    {
    case libvlc_MediaStateChanged:
		pfn = pAVPlayer->m_pfnMediaStateChanged;
		break;
    case libvlc_MediaPlayerPlaying:
        pfn = pAVPlayer->m_pfnPlaying;
        break;
    case libvlc_MediaPlayerEndReached:
        pfn = pAVPlayer->m_pfnEndReached;
        break;
    case libvlc_MediaPlayerEncounteredError:
		pfn = pAVPlayer->m_pfnMediaPlayerEncounteredError;
		break;
    case libvlc_MediaPlayerPositionChanged:
        pfn = pAVPlayer->m_pfnPosChanged;
        break;
    case libvlc_VlmMediaInstanceStatusError:
		pfn = pAVPlayer->m_pfnVlmMediaInstanceStatusError;
		break;
    default:
       break;
    }

    if (pfn)
    {
        pfn(pAVPlayer->GetFnData());  // 此回调函数还可以传入其他参数，除了data外，还有event的各种信息（如event->u.media_player_position_changed.new_position）等等，请自行扩展。
    }   
}
