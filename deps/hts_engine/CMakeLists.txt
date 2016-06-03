set(SOURCE
        lib/HTS_audio.c
        lib/HTS_engine.c
        lib/HTS_gstream.c
        lib/HTS_label.c
        lib/HTS_misc.c
        lib/HTS_model.c
        lib/HTS_pstream.c
        lib/HTS_sstream.c
        lib/HTS_vocoder.c
        )

set(HEADER
        HTS_engine.h
        lib/HTS_hidden.h
        )

add_library(HTSEngine ${SOURCE} ${HEADERS})

#install (TARGETS HTSEngine DESTINATION bin)
#install (FILES HEADERS DESTINATION include)