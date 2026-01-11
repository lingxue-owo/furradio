cmake_minimum_required(VERSION 3.10)

project(furradio LANGUAGES C)

add_library(bmp_library bmp.c)
add_library(wav_library wav.c)
add_library(ft8_library ft8/ft8_enc_msg.c ft8/ft8_enc_wave.c)
add_library(sstv_library sstv/sstv_type.c sstv/sstv_colorbar_gb3174.c)
