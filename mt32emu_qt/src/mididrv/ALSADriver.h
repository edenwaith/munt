#ifndef ALSA_MIDI_DRIVER_H
#define ALSA_MIDI_DRIVER_H

#include <alsa/asoundlib.h>

#include "MidiDriver.h"

class ALSAMidiDriver : public MidiDriver {
	Q_OBJECT
public:
	ALSAMidiDriver(Master *useMaster);
	~ALSAMidiDriver();
	void start();
	void stop();
	bool canSetPortProperties(MidiSession *);
	bool setPortProperties(MidiPropertiesDialog *mpd, MidiSession *);

private:
	snd_seq_t *snd_seq;
	pthread_t processingThreadID;
	volatile bool stopProcessing;
	QList<unsigned int> clients;
	QVarLengthArray<MT32Emu::Bit8u,MT32Emu::SYSEX_BUFFER_SIZE> sysexBuffer;

	static void *processingThread(void *userData);
	int alsa_setup_midi();
	void processSeqEvents();
	bool processSeqEvent(snd_seq_event_t *seq_event, SynthRoute *synthRoute);
	unsigned int getSourceAddr(snd_seq_event_t *seq_event);
	QString getClientName(unsigned int clientAddr);
	MidiSession *findMidiSessionForClient(unsigned int clientAddr);

signals:
	void mainWindowTitleContributionUpdated(const QString &);
};

#endif
