# Bare-metal cooperative scheduler for ARM Cortex-M4 (TM4C123) in C from scratch 

Dieses Lernprojekt fasst das Ergebnis meiner eigenständigen Entwicklung des Kooperativen Schedulers von Grund auf zusammen. 
Der Fokus lag darauf, mein angesammeltes theoretisches Wissen anzuwenden und grundlegende Embedded-Konzepte wie Hardware-Abstraktion, Scheduler-Design und modulare Firmwarestruktur praktisch umzusetzen.

Dieses Projekt bildet die Grundlage für mein nachfolgendes präemptives Scheduler-Projekt.

<img width="1338" height="198" alt="AnalyzerViewOnCooprativeScheduling2" src="https://github.com/user-attachments/assets/be00669d-d6d9-4208-8911-c9507ba3c036" />


Die PulseView-Messung zeigt den Ablauf des kooperativen Schedulers mit drei Tasks mit LED-Toggle-Funktion (Green, Red, Blue). 

Die Messung bestätigt das deterministische Verhalten des Schedulers.

Zu erkennen ist:
- Tasks werden immer leicht versetzt ausgeführt 
- Die jeweiligen Perioden werden ohne Drift eingehalten
- Blue-Task toggelt bei Betätigung des User-Switch (Fallende Flanke / active low) die blaue LED.  

**LED toggeln mit:**

Red-LED: Period = 250 ms || Green-LED: Period = 200 ms || Blue-LED = switch 1 pressed (active low)

## In PulseView zu sehende Tasks

     Task_t Task[] = {
        /* Task for red LED blinking */
        {
            .period = 250U,  
            .lastRun = 0U,   
            .sched = redLED  // Function to call
        },
        /* Task for Switch 1 debouncing and detection */
        {
            .period = 20U,  
            .lastRun = 0U,
            .sched = Switch_1
        },
        /* Task for greenLED blinking */
        {
            .period = 200U,   
            .lastRun = 0U,
            .sched = greenLED
        }
    };

## Kooperativer Scheduler für ARM Cortex-M4
    void Task_update(Task_t task[], uint32_t const numTasks, uint32_t now){
        for(uint8_t i = 0; i < numTasks; i++)
        {  
            if((now - task[i].lastRun) >= task[i].period)
            {
                // Run the task function (via function pointer)
                task[i].sched();
     
                task[i].lastRun += task[i].period;
            }
        }
    }
    
### Funktionsweise:
Der Scheduler iteriert zyklisch über alle Tasks und prüft, ob deren Ausführungszeitpunkt erreicht ist.
Ist dies der Fall, wird der entsprechende Task über einen Funktionspointer ausgeführt.

Durch das Inkrementieren von lastRun um die jeweilige Periode wird Timing-Drift verhindert, auch bei Timer-Überläufen.
Ein möglicher Nachteil dieser Methode ist, dass bei Überlast einzelne Task-Ausführungen übersprungen werden können.

### Einordnung des kooperativen Schedulers:

Ein kooperativer Scheduler eignet sich besonders für Systeme mit:

- kurzen Tasks
- klar definierten Ausführungszeiten
- geringer Systemkomplexität

Er ermöglicht ein deterministisches Verhalten bei minimalem Overhead.

Nachteile:

- Lange laufende Tasks blockieren andere Tasks („Task-Starvation“)
- Tasks müssen die CPU freiwillig abgeben
- Keine echte Parallelität oder Preemption
  
Dieses Konzept wird häufig in einfachen Embedded-Systemen ohne RTOS eingesetzt, da es bei geringer Komplexität ein gut vorhersagbares und deterministisches Systemverhalten ermöglicht.


## Architekturdiagramm:

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

## Entwicklungshinweis:

Dieses Projekt entstand als Lernprojekt im Bereich Embedded Systems. Während der Entwicklung habe ich KI-Tools für Feedback, Erklärungen und Unterstützung bei der Dokumentation (z.B. Doxygen) verwendet.

Der typische Entwicklungsprozess war:

Code schreiben → Feedback erhalten → Konzepte verstehen → Code überarbeiten.

Durch diese iterative Arbeitsweise konnte ich viele Embedded-Konzepte schneller verstehen und praktisch anwenden. Der finale Code ist von mir implementiert und wird vollständig von mir verstanden.

Das Ergebnis ist mein erstes größeres Embedded-Lernprojekt, bei dem ich angesammeltes theoretisches Wissen in praktische Firmwareentwicklung umgesetzt habe.


## CMSIS-Integration: 
Systematische Umstellung auf den Cortex Microcontroller Software Interface Standard für verbesserte Portabilität und Nutzung 
standardisierter Funktionen (NVIC, SysTick, SystemCoreClock).

## Tiva TM4C123 – Embedded C Projekt - Kooperativer Scheduler:

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
  
## Build info
- IAR Embedded Workbench (Arm)
- Tiva C Series LaunchPad TM4C123GXL

## Hardware:
- TI TM4C123GH6PM (ARM Cortex-M4)
- On-board LEDs
- User switch

