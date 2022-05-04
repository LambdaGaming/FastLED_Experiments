package com.lambdagaming.led_speech

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.speech.RecognitionListener
import android.speech.RecognizerIntent
import android.speech.SpeechRecognizer
import android.widget.TextView
import android.widget.ToggleButton
import com.android.volley.Request
import com.android.volley.toolbox.StringRequest
import com.android.volley.toolbox.Volley

private val Colors = mapOf(
	"white" to 0xFFFFFF,
	"black" to 0x000000,
	"read" to 0xFF0000,
	"green" to 0x00FF00,
	"blue" to 0x0000FF,
	"orange" to 0xFF5900,
	"yellow" to 0xFFFF00,
	"magenta" to 0xFF00FF,
	"cyan" to 0x00FFFF
)

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
		val result = matches?.get( 0 )
		text.text = result
		button.toggle()
		sendColor( result )
	}

	private fun sendColor( color: String? ) {
		Colors.forEach { entry ->
			if ( entry.key.lowercase() == color?.lowercase() ) {
				val queue = Volley.newRequestQueue( this )
				val request = StringRequest( Request.Method.POST, "http://192.168.1.208/state?color=${entry.value}", {}, {} )
				queue.add( request )
			}
		}
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
