#pragma once
#include <cmath>
#include <string>

namespace Frequency {
	enum WaveType { Sine, Square, Triangle, SawAnalog, SawDigital, Noise };


	static float pitchToSin(int pitch, double fPhase, WaveType waveType) {
		if (waveType == Noise) return sinf(rand());
		static const float freqs[]{ 27.500, 29.1353, 30.8677, 32.7032, 34.6479, 36.7081, 38.8909, 41.2035, 43.6536, 46.2493, 48.9995, 51.9130 };
		static const float PI = 3.14159f;
		//TODO: Which is faster: Calculate frequency per-frame or lookup table?
		float baseFreq = freqs[(pitch - 1) % 12];
		int octave = (pitch - 1) / 12;
		//Final frequency is the base frequency * 2^n, where n = octave
		float freq = baseFreq * (1 << octave);

		switch (waveType) {
		case WaveType::Sine:
			return sinf(freq * 2.0 * PI * fPhase); //Sine wave
		case WaveType::Square:
			return sinf(freq * 2.0 * PI * fPhase) > 0 ? 1.0 : -1.0; //Square wave
		case WaveType::SawDigital:
			return (2.0 / PI) * (freq * PI * fmod(fPhase, 1.0 / freq) - (PI / 2.0)); //Sawtooth digital
		case WaveType::SawAnalog:
			//TODO
		default:
			return 0.0f;
		}
	}

	static std::wstring pitchToWstring(int pitch, bool concat_octave = false) {
		static std::wstring PITCH_FLATS[]{ L"A ", L"Bb", L"B ", L"C ", L"Db", L"D ", L"Eb", L"E ", L"F ", L"Gb", L"G ", L"Ab" };
		if (concat_octave)
			return PITCH_FLATS[pitch % 12] + std::to_wstring(pitch / 12);
		else
			return PITCH_FLATS[pitch % 12];
	}
}