
"use strict";

window.SpeechRecognition = window.SpeechRecognition       ||
    window.webkitSpeechRecognition ||
    null;

class Integration {
    constructor(){



    }

    getResponse(message){

        return $.get("http://localhost:8080/sign/?say=hello", function(data, status){
            alert("Data: " + data + "\nStatus: " + status);
        });


    }

    restartSession(){
        $.get("localhost:8080/sign/?reset=")

    }
}

class Conversation {
    constructor(){

        this.transcription = document.getElementById('transcription');
        this.logbox = document.getElementById('log');

        this.integration = new Integration();

    }

    record(speaker, transcript){

        this.transcription.textContent = transcript + ' to which the arm says ' + this.integration.getResponse(transcript);;
    }

    log(message){
        this.logbox.innerHTML = message + '<br/>' + log.innerHTML;
    }

    beginConversation(){
        this.recognizer = new Recognizer();
        this.recognizer.startRecording();

    }
}

var conversation = new Conversation();

class Recognizer {

    constructor(){
        this.recognizer = new window.SpeechRecognition();
        this.recognizer.continuous = true;

        this.recognizer.onresult = function(event) {
            Recognizer.parseResult(event);
        };

        this.recognizer.onerror = function(event) {
            conversation.log('Recognition error: ' + event.message);
        };
    }

    static parseResult(event) {

        for (var i = event.resultIndex; i < event.results.length; i++) {
            if (event.results[i].isFinal) {
                conversation.record("Human Scum", event.results[i][0].transcript);
            }
        }

    }

    startRecording(){
        try {
            this.recognizer.start();
            conversation.log('Recognition started');
        } catch(ex) {
            conversation.log('Recognition error: ' + ex.message);
        }
    }

    stopRecording(){
        this.recognizer.stop();
    }

    restartRecording(){
        this.stopRecording();
        this.startRecording();
    }

}

