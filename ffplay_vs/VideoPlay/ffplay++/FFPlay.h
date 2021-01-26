#pragma once
/*!
 * \class 封装ffplay播放功能
 *
 * \brief 
 *
 * \author HXY10
 * \date 一月 2021
 */

#include "ffplayConfigure.h"
using namespace ffplay_hxy;

#define FF_QUIT_EVENT    (SDL_USEREVENT + 2)
#define FF_Seek_EVENT    (SDL_USEREVENT + 3)



enum PLAYSTATUE_FF
{
	PLAYSTATUE_FF_ING,
	PLAYSTATUE_FF_STOP,
	PLAYSTATUE_FF_PAUSE,
	PLAYSTATUE_FF_Finish
};

typedef void(*fStatusPlayCallBack)(PLAYSTATUE_FF ss, void *lParam);
typedef void(*fPlayProcessCallBack)(double nCurrentTime, double nTotalTime, void *lParam);

class CFFPlay
{
public:
	CFFPlay();
	~CFFPlay();

	//全局初始化
	static void InitFFmpeg();
	//反初始化
	static void UnInitFFmpeg();

	//设置音量
	void SetVolumeNum(unsigned int nNum);

	//是否禁用
	void SetDisableWithType(CONTENTTYPE cType,bool bDisable);

	//是否循环
	void SetLoop(bool bLoop);

	//设置显示模式
	void SetShowModel(int nShowModel);

	//设置 同步模式 
	void SetSyncType(AV_SYNC_TYPE sType);


	//设置状态回调
	void SetStausCall(fStatusPlayCallBack cb, void *lParm);

	//设置进度回调
	void SetPlayProcessCall(fPlayProcessCallBack cb, void *lPram);


	void SeekToTime(int nSec);

	//播放
	bool StartPlay(const char *szInputName, void *lwnd,int w,int h);

	void doExit();
	//停止
	void StopPlay();

	//暂停/继续
	void PauseAndContinuePlay();

	//静音
	void VolumeZero();

	
	//快进
	void FaseForwad(int nStep);

	//后退
	void BackStep(int nStep);

private:
	char m_szInputName[256];
	void *m_lwnd;

	fStatusPlayCallBack m_statusCB;
	void *m_statusCBParam;
	PLAYSTATUE_FF m_currentStatus;

	fPlayProcessCallBack m_processCB;
	void* m_processCBParam;

	double m_totalTimeLength;

	double m_incr; //快进快退时
	double  m_pos;

	int m_seekSec;// 

private:
	//锁管理
	static int lockmgr(void **mtx, enum AVLockOp op);

	static int decode_interrupt_cb(void *ctx);
	static void sdl_audio_callback(void *opaque, Uint8 *stream, int len);
	static int video_thread(void *arg);

	static int eventLoop_thread(void *arg);

	int decoder_decode_frame(Decoder *d, AVFrame *frame, AVSubtitle *sub);
	int get_video_frame(VideoState *is, AVFrame *frame);
	Frame *frame_queue_peek_writable(FrameQueue *f);
	void frame_queue_push(FrameQueue *f);
	int queue_picture(VideoState *is, AVFrame *src_frame, double pts, double duration, int64_t pos, int serial);
	
	void HandleVideoThread();

	static int subtitle_thread(void *arg);
	void HandleSubtitleThread();

	static int audio_thread(void *arg);
	void HandleAudioThread();


	void sync_clock_to_slave(Clock *c, Clock *slave);
	int packet_queue_get(PacketQueue *q, AVPacket *pkt, int block, int *serial);
	void frame_queue_next(FrameQueue *f);
	int get_master_sync_type(VideoState *is);
	double get_master_clock(VideoState *is);
	int synchronize_audio(VideoState *is, int nb_samples);
	inline int compute_mod(int a, int b);
	inline void fill_rectangle(int x, int y, int w, int h);
	int realloc_texture(SDL_Texture **texture, Uint32 new_format, int new_width, int new_height, SDL_BlendMode blendmode, int init_texture);
	void video_audio_display(VideoState *s);
	int audio_decode_frame(VideoState *is);
	void update_sample_display(VideoState *is, short *samples, int samples_size);
	void HandleAudio(Uint8 *stream, int len);

	//开始读取输入文件 的线程
	static int read_thread(void *arg);
	void print_error(const char *filename, int err);

	int is_realtime(AVFormatContext *s);
	void calculate_display_rect(SDL_Rect *rect, int scr_xleft, int scr_ytop, int scr_width, int scr_height, int pic_width, int pic_height, AVRational pic_sar);
	void set_default_window_size(int width, int height, AVRational sar);
	void HandleRead();

	VideoState * StreamOpen(const char *filename, AVInputFormat *iformat);
	void StreamClose(VideoState *is);
	void packet_queue_flush(PacketQueue *q);
	void packet_queue_destroy(PacketQueue *q);
	int packet_queue_put_private(PacketQueue *q, AVPacket *pkt);
	int packet_queue_put(PacketQueue *q, AVPacket *pkt);
	int packet_queue_put_nullpacket(PacketQueue *q, int stream_index);
	void packet_queue_start(PacketQueue *q);
	void packet_queue_abort(PacketQueue *q);
	void frame_queue_unref_item(Frame *vp);
	void frame_queue_destory(FrameQueue *f);
	void frame_queue_signal(FrameQueue *f);
	void decoder_abort(Decoder *d, FrameQueue *fq);
	void decoder_destroy(Decoder *d);
	double get_clock(Clock *c);
	void stream_toggle_pause(VideoState *is);
	void step_to_next_frame(VideoState *is);
	void stream_component_close(VideoState *is, int stream_index);
	void decoder_init(Decoder *d, AVCodecContext *avctx, PacketQueue *queue, SDL_cond *empty_queue_cond);
	int decoder_start(Decoder *d, int(*fn)(void *), void *arg);
	int64_t inline get_valid_channel_layout(int64_t channel_layout, int channels);
	int stream_component_open(VideoState *is, int stream_index);
	int stream_has_enough_packets(AVStream *st, int stream_id, PacketQueue *queue);
	int frame_queue_nb_remaining(FrameQueue *f);
	void stream_seek(VideoState *is, int64_t pos, int64_t rel, int seek_by_bytes);
	
	Frame *frame_queue_peek_readable(FrameQueue *f);
	int audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, struct AudioParams *audio_hw_params);

	void set_clock_speed(Clock *c, double speed);
	void check_external_clock_speed(VideoState *is);
	Frame *frame_queue_peek_last(FrameQueue *f);
	double vp_duration(VideoState *is, Frame *vp, Frame *nextvp);
	Frame *frame_queue_peek(FrameQueue *f);
	double compute_target_delay(double delay, VideoState *is);
	void update_video_pts(VideoState *is, double pts, int64_t pos, int serial);
	Frame *frame_queue_peek_next(FrameQueue *f);
	int video_open(VideoState *is);
	void get_sdl_pix_fmt_and_blendmode(int format, Uint32 *sdl_pix_fmt, SDL_BlendMode *sdl_blendmode);
	int upload_texture(SDL_Texture **tex, AVFrame *frame, struct SwsContext **img_convert_ctx);
	void video_image_display(VideoState *is);
	void video_display(VideoState *is);
	void video_refresh(void *opaque, double *remaining_time);
	int64_t frame_queue_last_pos(FrameQueue *f);
	void refresh_loop_wait_event(VideoState *is, SDL_Event *event);
	void stream_cycle_channel(VideoState *is, int codec_type);
	void seek_chapter(VideoState *is, int incr);
	void toggle_pause(VideoState *is);
	void toggle_mute(VideoState *is);
	void EventLoop(VideoState *is);

	int frame_queue_init(FrameQueue *f, PacketQueue *pktq, int max_size, int keep_last);
	int packet_queue_init(PacketQueue *q);
	void set_clock_at(Clock *c, double pts, int serial, double time);
	void set_clock(Clock *c, double pts, int serial);
	void init_clock(Clock *c, int *queue_serial);

	void DoSeek();
private:
	VideoState *m_is;

	int m_audio_disable; //禁用音频
	int m_video_disable; //禁用视频频
	int m_subtitle_disable; //禁用字幕

	int m_showModel;//设置显示模式，0显示视频，1显示音频波形，2显示音频频谱。缺省为0。如果视频不存在则自动选择2.
	int m_loop; //循环播放
	unsigned int m_volumeNum; // 音量范围是[0~100]
	AV_SYNC_TYPE m_av_sync_type; //同步方式

	int m_genpts; //生成pts
	int m_find_stream_info; //是否发现流信息
	int m_seek_by_bytes; //seek by bytes 0=off 1=on -1=auto
	int64_t m_start_time; //开始的时间

	//wanted_stream_spec[AVMEDIA_TYPE_AUDIO] },wanted_stream_spec[AVMEDIA_TYPE_VIDEO] wanted_stream_spec[AVMEDIA_TYPE_SUBTITLE] 设置播放哪一路
	 char* m_wanted_stream_spec[AVMEDIA_TYPE_NB];
	
	 //
	 int m_default_width;
	 int m_default_height;

	 int m_infinite_buffer;//设置无极限的播放器buffer，这个选项常见于实时流媒体播放场景
	 int m_autoexit; //自动退出

	 int64_t m_duration; //播放多少秒

	 int m_lowres;
	 //强制使用的编码器名称
	 char m_audio_codec_name[128];
	 char m_subtitle_codec_name[128];
	 char m_video_codec_name[128] ;

	 int m_fast; //	 非标准化规范的多媒体兼容优化
	 int m_decoder_reorder_pts; //let decoder reorder pts 0=off 1=on -1=auto

	int m_framedrop;//drop frames when cpu is too slow

	int m_display_disable; //disable graphical display
	double m_rdftspeed ;//"rdft speed", "msecs"

	//bool m_bStopEvent; //是否停之 事件循环

private:
	AVPacket m_flush_pkt;
	AVInputFormat *m_file_iformat;
	AVDictionary *m_format_opts; 
	int64_t m_audio_callback_time;

	int64_t m_cursor_last_shown;
	SDL_Thread *m_eventThread;
private:
	 SDL_Window *m_window;
	 SDL_Renderer *m_renderer;
	 SDL_RendererInfo m_renderer_info = { 0 };
	 SDL_AudioDeviceID m_audio_dev;
};

