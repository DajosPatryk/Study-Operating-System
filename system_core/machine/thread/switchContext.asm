%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
	mov eax, [esp + 4]          ; Parameter void** "from"
	mov ecx, [esp + 8]          ; Parameter void** "to"
	
	push ebp					; nicht fluchtige Registers retten
	push ebx
	push esi
	push edi
	
	mov [eax], esp              ; speichere esp in Parameter "from"
	mov esp, [ecx]              ; lade esp from parameter "from" --> Kontextwechsel
								; hier lauft andere Programm
	pop edi						; nach Ruckkehr gerettete Register Inhalte wiederstellen
	pop esi
	pop ebx
	pop ebp
	ret		; Ruecksprung zum Aufrufer

