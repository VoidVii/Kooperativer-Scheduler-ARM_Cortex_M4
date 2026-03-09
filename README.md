# Learning Project – Embedded Systems
Bare-metal cooperative scheduler for ARM Cortex-M4 (TM4C123)

Kooperativer Scheduler für ARM Cortex-M4

Dieses Projekt implementiert einen einfachen cooperative task scheduler auf Basis des SysTick Timers. Ziel des Projekts war es, ein besseres Verständnis für Embedded-System-Architektur, Hardware-Abstraktion und zeitgesteuerte Task-Ausführung ohne RTOS zu entwickeln.

# Architekturdiagramm:

    SysTick (1ms)
        |
        v
    GetTickCounter()
        |
        v
    Task Scheduler
        |
        +---- LED Tasks
        |
        +---- Switch Debounce Task

# Entwicklungshinweis:

Dieses Projekt entstand als Lernprojekt im Bereich Embedded Systems. Während der Entwicklung habe ich KI-Tools für Feedback, Erklärungen und Unterstützung bei der Dokumentation (z.B. Doxygen) verwendet.

Der typische Entwicklungsprozess war:

Code schreiben → Feedback erhalten → Konzepte verstehen → Code überarbeiten.

Durch diese iterative Arbeitsweise konnte ich viele Embedded-Konzepte schneller verstehen und praktisch anwenden. Der finale Code ist von mir implementiert und wird vollständig von mir verstanden.

Das Ergebnis ist mein erstes größeres Embedded-Lernprojekt, bei dem ich versucht habe, theoretisches Wissen mit praktischer Firmwareentwicklung zu verbinden.

Der Fokus lag darauf, grundlegende Embedded-Konzepte wie Hardware-Abstraktion, Scheduler-Design und modulare Firmwarestruktur praktisch umzusetzen.

# Tiva TM4C123 – Embedded C Projekt - Kooperativer Scheduler:

In diesem Lernprojekt habe ich ein komplettes Embedded-System auf Basis des Tiva TM4C123 (ARM Cortex-M4) entwickelt. Die Schwerpunkte lagen auf:

- Hardware-Abstraktion:
  Entwicklung eigener GPIO-Treiber mit Pointer-Arithmetik und Bit-Manipulation (AHB-basiert)
- Objektorientierung in C:
  Implementierung von LED- und Switch-Objekten mit Funktionspointern für flexible Hardware-Ansteuerung
- Kooperativer Scheduler:
  Eigenentwicklung eines kooperativen Task-Schedulers für zeitgesteuerte periodische Abläufe (Foreground/Background-Architektur)
- Dokumentation:
  Code-Dokumentation mit Doxygen
- Debugging & Problemlösung:
  Umgang mit Hardware-Besonderheiten (Lock/Commit-Register, Bit-spezifische Adressierung, volatile)

# Hardware:

- TI TM4C123GH6PM (ARM Cortex-M4)
- On-board LEDs
- User switch
