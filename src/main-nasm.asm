	global getDivisorCount_variant1, getDivisorCount_variant2
	
	; * * * * * * * * * 
	; VARIANT 1
	; * * * * * * * * * 
	
getDivisorCount_variant1:
	pop ecx                      ; save return address in ecx
	pop edx                      ; save first parameter (input value) in edx
	
	push ecx                     ; push return address back to stack
	
	push ebx                     ; save value of ebx (needs to be callee - saved)
	push edi                     ; save value of edi
	
	mov edi, edx                 ; now save input value in edi
	
	mov ebx, 0                   ; init value in which the count of dividable integers will be saved
	mov ecx, 0                   ; init divider (loop counter)
	
mainLoop:
	cmp ecx, edi                 ; while (ecx != edi) ...
	je loopFinish                ; break loop if ecx == edi
	
	inc ecx                      ; increase loop variable inside loop
	
	mov eax, edi                 ; set up number (eax) which we divide by ecx
	mov edx, 0                   ; edx needs to be cleared first before doing div operation
	div ecx                      ; divide eax by ecx
	
	cmp edx, 0                   ; edx stores the remainder of the last div operation, if edx is 0 then eax is dividable by ecx
	jne mainLoop                 ; iterate on if the remainder is not equal to 0
	
	inc ebx                      ; increment ebx (count of dividable numbers) if the remainder is 0
	jmp mainLoop
	
loopFinish:
	mov eax, ebx                 ; move ebx's value to return value register (eax)
	
	pop edi                      ; restore edi
	pop ebx                      ; restore ebx
	
	ret
	
	
	
	
	; * * * * * * * * * 
	; VARIANT 2
	; * * * * * * * * * 
	
getDivisorCount_variant2:
	push ebp                     ; store base pointer on stack
	mov ebp, esp                 ; save stack pointer in ebp
	
	push ebx                     ; save ebx
	push edi                     ; save edi
	
	mov edi, [ebp + 8]           ; fetch first parameter (input value)
	
	mov eax, edi                 ; save input number temporarily in eax
	neg edi                      ; negate input number
	cmp edi, eax
	cmovl edi, eax               ; restore original number only if edi is negative now (edi < eax): edi is now absolute
	
	mov ebx, 0                   ; init register in which the count of dividable integers will be saved
	mov ecx, edi                 ; init divider (loop variable), set it to input value to loop down
	inc ecx
	
	cmp edi, 0
	je loopFinish2               ; early out if input is 0
	
mainLoop2:
	mov eax, edi                 ; set up number (eax) which we divide by ecx
	mov edx, 0                   ; edx needs to be cleared first before doing div operation
	div ecx                      ; divide eax by ecx
	
	cmp edx, 0                   ; if edx is 0 then eax is dividable by ecx
	jne loopOn2                  ; if the remainder is not equal to 0 then keep looping without increasing ebx
	
	inc ebx                      ; increment count of dividable numbers
	
loopOn2:
	loop mainLoop2               ; keep looping till ecx is 0: for(int ecx = edi, ecx > 0; ecx - - )...
	
loopFinish2:
	mov ecx, [ebp + 12]          ; store address of second parameter (pointer to result) in ecx
	
	mov [ecx], ebx               ; save return value in second parameter
	
	pop edi                      ; restore edi
	pop ebx                      ; restore ebx
	
	pop ebp                      ; restore base pointer
	
	ret