
/*  godot_videodecoder.h                                                 */

#ifndef GODOT_NATIVEVIDEODECODER_H
#define GODOT_NATIVEVIDEODECODER_H

#include <gdnative/gdnative.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GODOTAV_API_MAJOR 0
#define GODOTAV_API_MINOR 1

typedef struct
{
	godot_gdnative_api_version version;
	void *next;
	void *(*constructor)(godot_object *);
	void (*destructor)(void *);
	const char *(*get_plugin_name)();
	const char **(*get_supported_extensions)(int *count);
	godot_bool (*open_file)(void *, void *); // data struct, and a FileAccess pointer
	godot_real (*get_length)(const void *);
	godot_real (*get_playback_position)(const void *);
	void (*seek)(void *, godot_real);
	void (*set_audio_track)(void *, godot_int);
	void (*update)(void *, godot_real);
	godot_packed_byte_array *(*get_videoframe)(void *);
	godot_int (*get_audioframe)(void *, float *, int);
	godot_int (*get_channels)(const void *);
	godot_int (*get_mix_rate)(const void *);
	godot_vector2 (*get_texture_size)(const void *);
} godot_videodecoder_interface_gdnative;

typedef int (*GDNativeAudioMixCallback)(void *, const float *, int);

// FileAccess wrappers for custom FFmpeg IO
godot_int GDAPI godot_videodecoder_file_read(void *file_ptr, uint8_t *buf, int buf_size);
int64_t GDAPI godot_videodecoder_file_seek(void *file_ptr, int64_t pos, int whence);
void GDAPI godot_videodecoder_register_decoder(const godot_videodecoder_interface_gdnative *p_interface);

#ifdef __cplusplus
}
#endif

#endif /* GODOT_NATIVEVIDEODECODER_H */
