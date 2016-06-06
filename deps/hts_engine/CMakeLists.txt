set(SOURCE
        src/HTS_audio.c
        src/HTS_engine.c
        src/HTS_gstream.c
        src/HTS_label.c
        src/HTS_misc.c
        src/HTS_model.c
        src/HTS_pstream.c
        src/HTS_sstream.c
        src/HTS_vocoder.c
        )

set(HEADER
        HTS_engine.h
        src/HTS_hidden.h
        )

add_library(HTSEngine ${SOURCE} ${HEADERS})

#install (TARGETS HTSEngine DESTINATION bin)
#install (FILES HEADERS DESTINATION include)