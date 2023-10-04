audio-mixer
===========
### TODOs
- [ ] Summing
- [ ] baremetal
- [ ] unit tests (using ffmpeg, etc.)
    - wip: `ffmpeg -i "440Hz.wav" -i "880Hz.wav" -filter_complex amix=inputs=2:duration=first:dropout_transition=3:normalize=0 -c:a pcm_s16le "ffmpeg-sum.wav"`
- [ ] VST (2, 3) host
- [ ] in memory playback using portaudio

### Tools
- [Online Tone Generator - Free, Simple and Easy to Use](https://onlinetonegenerator.com/)

### Using
- [dirkarnez/libsndfile-prebuilt](https://github.com/dirkarnez/libsndfile-prebuilt)
- [dirkarnez/portaudio-prebuilt](https://github.com/dirkarnez/portaudio-prebuilt)
