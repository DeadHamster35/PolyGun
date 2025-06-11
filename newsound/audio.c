#include <os.h>
#include <stdio.h>
#include <nusys.h>
//#include <nualsgi_n.h>
#include "actors.h"
#include "main.h"
#include "segment.h"
#include "levels.h"
#include "player.h"
#include "graphic.h"
#include "collision.h"
#include "pathfinding.h"
#include "memory.h"
#include "weapon.h"


#include <nualsgi_n.h>

musHandle	seqHandle = 0;
musHandle	sndHandle = 0;

int ptr_buf[NU_AU_SAMPLE_SIZE]__attribute__((aligned(16)));
int tune_buf[NU_AU_SONG_SIZE]__attribute__((aligned(16)));
int sfx_buf[NU_AU_SE_SIZE]__attribute__((aligned(16)));


u8	*song_start_list[] = {
    MUSIC1_START,
    MUSIC2_START,
    MUSIC3_START,
};

u8	*song_end_list[] = {
    MUSIC1_END,
    MUSIC2_END,
    MUSIC3_END,
};


/* Provide playback and control of audio by the button of the controller */
void soundCheck(void)
{
  static int snd_no = 0;
  static int seq_no = 0;
  static int start_song_flag = 0;

  /* The sequence is actually stopped until the next frame.  After a wait of 1 frame, the sequence is loaded by DMA (overwrite).  */

  /* If the sequence was stopped in the previous frame, a new sequence is started. */
  if(start_song_flag)
    {
      /* Read the sequences. */
      LoadDMA((void *)tune_buf, (void *)song_start_list[seq_no], song_end_list[seq_no]-song_start_list[seq_no]);
      /* Play a sequence. */
      seqHandle = MusStartSong(tune_buf);

      /* Reset the flag. */
      start_song_flag = 0;
    }

  /* Possible to play audio in order by right and left of the cross key */
  if((contdata[0].trigger & U_JPAD) || (contdata[0].trigger & D_JPAD))
    {
      if(contdata[0].trigger & U_JPAD)
	{
	  seq_no--;
	  if(seq_no < 0) seq_no = 2;
	}
      else
	{
	  seq_no++;
	  if(seq_no > 2) seq_no = 0;
	}	  

      MusStop(MUSFLAG_SONGS,0);

      /* Set the flag so that a new sequence begins at the next frame. */
      start_song_flag = 1;
    }


  /* The order in which audio is played can be determined using the right and left sides of the cross key. */
  if((contdata[0].trigger & L_JPAD) || (contdata[0].trigger & R_JPAD))
    {
      if(snd_no)
	MusHandleStop(sndHandle,0);

      if(contdata[0].trigger & L_JPAD)
	{
	  snd_no--;
	  if(snd_no < 1) snd_no = 5;
	}
      else
	{
	  snd_no++;
	  if(snd_no > 5) snd_no = 1;
	}	  

      sndHandle = MusStartEffect(snd_no);

    }

  /* Change tempo of sequence playback by L and R buttons */
  if((contdata[0].trigger & L_TRIG) || (contdata[0].trigger & R_TRIG))
    {
      if(contdata[0].trigger & L_TRIG)
	MusHandleSetTempo(seqHandle,0x100);
      else
	MusHandleSetTempo(seqHandle,0x40);
    }

  /* Stop sequence playback by the Z button */
  if( contdata[0].trigger & Z_TRIG )
    MusHandleStop(seqHandle,200);
}




/* Set audio data */
void setAudioData(void)
{
        


    musConfig c;

    c.control_flag	= 0; /* Set to MUSCONTROL_RAM if wbk file also placed in RAM */
    c.channels		= NU_AU_CHANNELS; /* Maximum total number of channels */
    c.sched		= NULL; /* Ignore */
    c.thread_priority	= NU_AU_MGR_THREAD_PRI; /* Usually not changed */
    c.heap		= (unsigned char*)NU_AU_HEAP_ADDR; /* Usually not changed */
    c.heap_length	= NU_AU_HEAP_SIZE;
    c.ptr		= NULL; /* Can set the default ptr file */
    c.wbk		= NULL; /* Can set the default wbk file */
    c.default_fxbank	= NULL; /* Can set the default bfx file  */
    c.fifo_length	= NU_AU_FIFO_LENGTH; /* Usually not changed */
    c.syn_updates	= NU_AU_SYN_UPDATE_MAX;
    c.syn_output_rate	= 44100;
	/* Usually set to NU_AU_OUTPUT_RATE=32kHz or less*/
    c.syn_rsp_cmds	= NU_AU_CLIST_LEN;
    c.syn_retraceCount	= 2; /* Usually not changed */
    c.syn_num_dma_bufs	= NU_AU_DMA_BUFFER_NUM;
    c.syn_dma_buf_size	= NU_AU_DMA_BUFFER_SIZE;

    /* Initialize the Audio Manager. */
    nuAuStlMgrInit(&c);

    /* Register the PRENMI function.*/
    nuAuPreNMIFuncSet(nuAuPreNMIProc);


    /* Read and register the sample bank. */
    LoadDMA((void *)ptr_buf, (void *)PBANK_START, PBANK_END-PBANK_START);
    MusPtrBankInitialize(ptr_buf, WBANK_START);

    /* Read and register the sound effects. */
    LoadDMA((void *)sfx_buf, (void *)SFX_START, SFX_END-SFX_START);
    MusFxBankInitialize(sfx_buf);

}



void InitAudioOld()
{

    /* Register the bank to the sequence player */
    //nuAuSeqPlayerBankSet(_midibankSegmentRomStart,
//                         _midibankSegmentRomEnd - _midibankSegmentRomStart,
//                         _miditableSegmentRomStart);
    /* Register MIDI sequence data to the sequence player */
    //nuAuSeqPlayerSeqSet(_seqSegmentRomStart);
    /* Register the bank to the sound player */
    //nuAuSndPlayerBankSet(_sfxbankSegmentRomStart,
//                         _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart,
//                         _sfxtableSegmentRomStart);
 
}
