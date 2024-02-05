#ifndef _BROADCASTRADIO_H_
#define _BROADCASTRADIO_H_

/******************************
 * Write mode register values *
 ******************************/

/* First register */
#define BROADCASTRADIO_MUTE        0x80    /* Mutes output */
#define BROADCASTRADIO_SEARCH        0x40    /* Activates station search */
/* Bits 0-5 for divider MSB */

/* Second register */
/* Bits 0-7 for divider LSB */

/* Third register */

/* Station search from botton to up */
#define BROADCASTRADIO_SEARCH_UP    0x80

/* Searches with ADC output = 10 */
#define BROADCASTRADIO_SRCH_HIGH_LVL    0x60

/* Searches with ADC output = 10 */
#define BROADCASTRADIO_SRCH_MID_LVL    0x40

/* Searches with ADC output = 5 */
#define BROADCASTRADIO_SRCH_LOW_LVL    0x20

/* if on, div=4*(Frf+Fif)/Fref otherwise, div=4*(Frf-Fif)/Freq) */
#define BROADCASTRADIO_HIGH_LO_INJECT    0x10

/* Disable stereo */
#define BROADCASTRADIO_MONO        0x08

/* Disable right channel and turns to mono */
#define BROADCASTRADIO_MUTE_RIGHT    0x04

/* Disable left channel and turns to mono */
#define BROADCASTRADIO_MUTE_LEFT    0x02

#define BROADCASTRADIO_PORT1_HIGH    0x01

/* Fourth register */
#define BROADCASTRADIO_PORT2_HIGH    0x80
/* Chips stops working. Only I2C bus remains on */
#define BROADCASTRADIO_STDBY        0x40

/* Japan freq (76-108 MHz. If disabled, 87.5-108 MHz */
#define BROADCASTRADIO_JAPAN_BAND    0x20

/* Unselected means 32.768 KHz freq as reference. Otherwise Xtal at 13 MHz */
#define BROADCASTRADIO_XTAL_32768    0x10

/* Cuts weak signals */
#define BROADCASTRADIO_SOFT_MUTE    0x08

/* Activates high cut control */
#define BROADCASTRADIO_HIGH_CUT_CTRL    0x04

/* Activates stereo noise control */
#define BROADCASTRADIO_ST_NOISE_CTL    0x02

/* If activate PORT 1 indicates SEARCH or else it is used as PORT1 */
#define BROADCASTRADIO_SRCH_IND    0x01

/* Fifth register */

/* By activating, it will use Xtal at 13 MHz as reference for divider */
#define BROADCASTRADIO_PLLREF_ENABLE    0x80

/* By activating, deemphasis=50, or else, deemphasis of 50us */
#define BROADCASTRADIO_DEEMPH_75    0X40

/*****************************
 * Read mode register values *
 *****************************/

/* First register */
#define BROADCASTRADIO_READY_FLAG_MASK    0x80
#define BROADCASTRADIO_BAND_LIMIT_MASK    0X40
/* Bits 0-5 for divider MSB after search or preset */

/* Second register */
/* Bits 0-7 for divider LSB after search or preset */

/* Third register */
#define BROADCASTRADIO_STEREO_MASK    0x80
#define BROADCASTRADIO_IF_CNTR_MASK    0x7f

/* Fourth register */
#define BROADCASTRADIO_ADC_LEVEL_MASK    0xf0

/* should be 0 */
#define BROADCASTRADIO_CHIP_ID_MASK    0x0f

/* Fifth register */
/* Reserved for future extensions */
#define BROADCASTRADIO_RESERVED_MASK    0xff

/* internal constants */
#define BROADCASTRADIO_SEARCH_DIR_UP 1
#define BROADCASTRADIO_SEARCH_DIR_DOWN 2

#include <Arduino.h>

struct broadcast_radio_ctrl
{
  unsigned int port1:1;
  unsigned int port2:1;
  unsigned int high_cut:1;
  unsigned int st_noise:1;
  unsigned int soft_mute:1;
  unsigned int japan_band:1;
  unsigned int deemph_75:1;
  unsigned int pllref:1;
  unsigned int xtal_freq;
};

class BroadcastRadio {
	private:
		broadcast_radio_ctrl ctrl_data;
		int HILO;
	protected:
		int hilo_optimal (unsigned long freq);
		void set_frequency (int hilo, double freq);
		int ready (unsigned char *buf);
		int bl_reached (unsigned char *buf);
	public:
		BroadcastRadio();
		BroadcastRadio(double initial_freq);
		void set_frequency (double freq);
		int read_status (unsigned char *buf);
		int signal_level (unsigned char *buf);
		int stereo (unsigned char *buf);
		double frequency_available (unsigned char *buf);
		void search_up (unsigned char *buf);
		void search_down (unsigned char *buf);
		int process_search (unsigned char *buf, int search_dir);
		void init();
};

#endif  // _BROADCASTRADIO_H_
