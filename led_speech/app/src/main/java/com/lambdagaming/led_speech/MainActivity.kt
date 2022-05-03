package com.lambdagaming.led_speech

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.speech.RecognitionListener
import android.speech.RecognizerIntent
import android.speech.SpeechRecognizer
import android.widget.TextView
import android.widget.ToggleButton

class MainActivity : AppCompatActivity(), RecognitionListener {
	override fun onCreate(savedInstanceState: Bundle? ) {
		super.onCreate( savedInstanceState )
		setContentView( R.layout.activity_main )

		val button = findViewById<ToggleButton>( R.id.toggleButton )
		val speech = SpeechRecognizer.createSpeechRecognizer( this )
		if ( SpeechRecognizer.isRecognitionAvailable( this ) ) {
			speech.setRecognitionListener( this )
			val recognizerIntent = Intent( RecognizerIntent.ACTION_RECOGNIZE_SPEECH )
			recognizerIntent.putExtra( RecognizerIntent.EXTRA_LANGUAGE_PREFERENCE, "US-en" )
			recognizerIntent.putExtra( RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM )
			recognizerIntent.putExtra( RecognizerIntent.EXTRA_MAX_RESULTS, 1 )
			button.setOnCheckedChangeListener { _, isChecked ->
				if ( isChecked ) {
					speech.startListening( recognizerIntent )
					button.textOn = "Listening..."
				}
				else {
					speech.stopListening()
					button.textOff = "Off"
				}
			}
		}
	}

	override fun onResults( results: Bundle? ) {
		val text = findViewById<TextView>( R.id.textView )
		val button = findViewById<ToggleButton>( R.id.toggleButton )
		val matches = results!!.getStringArrayList( SpeechRecognizer.RESULTS_RECOGNITION )
		text.text = matches?.get( 0 )
		button.toggle()
	}

	override fun onReadyForSpeech(p0: Bundle?) {}
	override fun onBeginningOfSpeech() {}
	override fun onRmsChanged(p0: Float) {}
	override fun onBufferReceived(p0: ByteArray?) {}
	override fun onEndOfSpeech() {}
	override fun onError(p0: Int) {}
	override fun onPartialResults(p0: Bundle?) {}
	override fun onEvent(p0: Int, p1: Bundle?) {}
}
