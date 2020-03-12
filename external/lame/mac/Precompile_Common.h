/*	Common Precompiled headers for LAME on Macintosh		Precompiled header source for building
 * LAME on Macintosh using CodeWarrior.	Includes most definitions normally generated by configure
 * in config.h,	except for the ones that vary from subproject to subproject*/
#define TARGET_MAC_DLL 1 #ifndef _ALL_SOURCE /* #undef _ALL_SOURCE */
    #endif #define HAVE_ALLOCA 1 #define HAVE_LONG_DOUBLE 1 #define STDC_HEADERS 1 #define TIME_WITH_SYS_TIME 1 #define WORDS_BIGENDIAN 1 #define uint8_t
        UInt8 #define uint16_t UInt16 #define uint32_t
            UInt32 #define uint64_t unsigned long long #define ieee854_float80_t long double #define ieee754_float64_t double #define ieee754_float32_t float #define SIZEOF_DOUBLE 8 #define SIZEOF_FLOAT 4 #define SIZEOF_INT 4 #define SIZEOF_LONG 4 #define SIZEOF_LONG_LONG 8 #define SIZEOF_SHORT 2 #define SIZEOF_UNSIGNED_INT 4 #define SIZEOF_UNSIGNED_LONG 4 #define SIZEOF_UNSIGNED_LONG_LONG 8 #define SIZEOF_UNSIGNED_SHORT 2 #define HAVE_GETTIMEOFDAY 1 #define HAVE_SOCKET 1 #define HAVE_STRTOL 1 #define HAVE_ERRNO_H 1 #define HAVE_FCNTL_H 1 #define HAVE_LIMITS_H 1 #define HAVE_STRING_H 1 #define HAVE_SYS_TIME_H 1 #define HAVE_UNISTD_H 1 #define PACKAGE
    "lame" #define VERSION
    "3.91" #define PROTOTYPES 1 #define HAVE_IEEE854_FLOAT80 1 #define LIMIT_STACK_USAGE 1  //	The
                                                                                            //following
                                                                                            //definitions
                                                                                            //have
                                                                                            //been
                                                                                            //pulled
                                                                                            //out to
                                                                                            //specific
                                                                                            //targets'  //		pch files:  //			LAME_LIBRARY_BUILD			1 for building the DLL  //			LIBSNDFILE					1 for building with LibSndFile, applies  //											only to CLI encoder  //			NOANALYSIS					1 for building without hooks for the  //											MP3 frame analyzer  //			HAVE_MPGLIB					1 for building with MP3 decoding library.  //											Note MPGLIB, unlike LAME itself, is  //											GPL as opposed to LGPL and thus unsuitable  //											for compilation into a DLL that would be used  //											from a closed-source app.  //			USE_LAYER_1					1 for building layer-1 decoding into MPGLIB  //			USE_LAYER_2					1 for building layer-2 decoding into MPGLIB  //			HAVE_VORBIS					1 for building vorbis support  //			NDEBUG						1 for building with debug info  //			BRHIST						1 for histogram display in CLI encoder
    #define HAVE_TERMCAP 1 #include < MacTypes.h >