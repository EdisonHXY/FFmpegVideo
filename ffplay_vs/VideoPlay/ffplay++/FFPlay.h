#pragma once
/*!
 * \class ��װffplay���Ź���
 *
 * \brief 
 *
 * \author HXY10
 * \date һ�� 2021
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

	//ȫ�ֳ�ʼ��
	static void InitFFmpeg();
	//����ʼ��
	static void UnInitFFmpeg();

	//��������
	void SetVolumeNum(unsigned int nNum);

	//�Ƿ����
	void SetDisableWithType(CONTENTTYPE cType,bool bDisable);

	//�Ƿ�ѭ��
	void SetLoop(bool bLoop);

	//������ʾģʽ
	void SetShowModel(int nShowModel);

	//���� ͬ��ģʽ 
	void SetSyncType(AV_SYNC_TYPE sType);


	//����״̬�ص�
	void SetStausCall(fStatusPlayCallBack cb, void *lParm);

	//���ý��Ȼص�
	void SetPlayProcessCall(fPlayProcessCallBack cb, void *lPram);


	void SeekToTime(int nSec);

	//����
	bool StartPlay(const char *szInputName, void *lwnd,int w,int h);

	void doExit();
	//ֹͣ
	void StopPlay();

	//��ͣ/����
	void PauseAndContinuePlay();

	//����
	void VolumeZero();

	
	//���
	void FaseForwad(int nStep);

	//����
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

	double m_incr; //�������ʱ
	double  m_pos;

	int m_seekSec;// 

private:
	//������
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

	//��ʼ��ȡ�����ļ� ���߳�
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

	int m_audio_disable; //������Ƶ
	int m_video_disable; //������ƵƵ
	int m_subtitle_disable; //������Ļ

	int m_showModel;//������ʾģʽ��0��ʾ��Ƶ��1��ʾ��Ƶ���Σ�2��ʾ��ƵƵ�ס�ȱʡΪ0�������Ƶ���������Զ�ѡ��2.
	int m_loop; //ѭ������
	unsigned int m_volumeNum; // ������Χ��[0~100]
	AV_SYNC_TYPE m_av_sync_type; //ͬ����ʽ

	int m_genpts; //����pts
	int m_find_stream_info; //�Ƿ�������Ϣ
	int m_seek_by_bytes; //seek by bytes 0=off 1=on -1=auto
	int64_t m_start_time; //��ʼ��ʱ��

	//wanted_stream_spec[AVMEDIA_TYPE_AUDIO] },wanted_stream_spec[AVMEDIA_TYPE_VIDEO] wanted_stream_spec[AVMEDIA_TYPE_SUBTITLE] ���ò�����һ·
	 char* m_wanted_stream_spec[AVMEDIA_TYPE_NB];
	
	 //
	 int m_default_width;
	 int m_default_height;

	 int m_infinite_buffer;//�����޼��޵Ĳ�����buffer�����ѡ�����ʵʱ��ý�岥�ų���
	 int m_autoexit; //�Զ��˳�

	 int64_t m_duration; //���Ŷ�����

	 int m_lowres;
	 //ǿ��ʹ�õı���������
	 char m_audio_codec_name[128];
	 char m_subtitle_codec_name[128];
	 char m_video_codec_name[128] ;

	 int m_fast; //	 �Ǳ�׼���淶�Ķ�ý������Ż�
	 int m_decoder_reorder_pts; //let decoder reorder pts 0=off 1=on -1=auto

	int m_framedrop;//drop frames when cpu is too slow

	int m_display_disable; //disable graphical display
	double m_rdftspeed ;//"rdft speed", "msecs"

	//bool m_bStopEvent; //�Ƿ�֮ͣ �¼�ѭ��

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

