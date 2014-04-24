#include "audio-stream-stop.h"

using namespace std;

AudioStreamStopCommand::AudioStreamStopCommand() :
		DaemonCommand("audio-stream-stop", "audio-stream-stop <audio stream id>", "Stop an audio stream.") {
	addExample(new DaemonCommandExample("audio-stream-stop 1",
						"Status: Ok"));
	addExample(new DaemonCommandExample("audio-stream-stop 2",
						"Status: Error\n"
						"Reason: No Audio Stream with such id."));
}

void AudioStreamStopCommand::exec(Daemon *app, const char *args) {
	int id;
	if (sscanf(args, "%d", &id) == 1) {
		AudioStream *stream = app->findAudioStream(id);
		if (stream == NULL) {
			app->sendResponse(Response("No Audio Stream with such id."));
			return;
		}
		audio_stream_stop(stream);
		app->removeAudioStream(id);
		app->sendResponse(Response());
	} else {
		app->sendResponse(Response("Missing/Incorrect parameter(s)."));
	}
}