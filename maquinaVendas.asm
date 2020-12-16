#Diego Correa Faria Alvarenga
#Maquina de vendas, dá troco otimizado, atualiza dinheiro dentro da maquina

.data

#Quantidade de dinheiro na maquina
reais20:    .word 10
reais10:    .word 10
reais5:     .word 100
reais2:     .word 100
real1:      .word 100
centavos50: .word 1000
centavos25: .word 1000
centavos10: .word 1000
centavos5:  .word 1000

#valores
valorProduto:       .word 4075
valorInseridoTotal: .word 0
valorInserido:      .word 0
troco:              .word 0

#texto

bemVindoMsg:            .asciiz "Bem vindo a maquina de vendas.\n "
valInseridoMsg:         .asciiz "\nValor Inserido até o momento: "
aguardandoPagamentoMsg: .asciiz "\n\nAguardando pagamento...\nDigite -1 para desistir.\n"
trocoMsg:               .asciiz "\nTroco: R$"
valorProdutoMsg:	.asciiz "\nValor do produto selecionado: R$"
valorPagoMsg:		.asciiz "\nValor pago: R$"
trocoOutMsg:		.asciiz "\nComo o troco sai da maquina:\n"

reais20Msg:    .asciiz "\n20 reais: "
reais10Msg:    .asciiz "\n10 reais: "
reais5Msg:     .asciiz "\n5 reais: "
reais2Msg:     .asciiz "\n2 reais: "
real1Msg:      .asciiz "\n1 real: "
centavos50Msg: .asciiz "\n50 centavos: "
centavos25Msg: .asciiz "\n25 centavos: "
centavos10Msg: .asciiz "\n10 centavos: "
centavos5Msg:  .asciiz "\n5 centavos: "

pontoMsg: .asciiz "."




.text
	main:
		
		# Inicializando registros
		
		lw $t9, valorProduto		#t9 = valorProduto
		lw $t1, valorInseridoTotal 	#t1 = valorInseridoTotal  
		
		
		lw $s0, reais20
		lw $s1, reais10
		lw $s2, reais5
		lw $s3, reais2
		lw $s4, real1
		lw $s5, centavos50
		lw $s6, centavos25
		lw $s7, centavos10
			
		#mensagem de boas vindas																	
		li $v0, 4
		la $a0, bemVindoMsg
		syscall						
											
																	
				while: 
					
				
					
					li $v0, 4
					la $a0, valorPagoMsg
					syscall
					
					jal printValorInseridoTotal 
					
					li $v0, 4
					la $a0, valorProdutoMsg
					syscall
					
					jal displayValorProduto
					
					li $v0, 4
					la $a0, trocoMsg
					syscall
					
					jal displayTroco
					
					li $v0, 4
					la $a0, aguardandoPagamentoMsg
					syscall
					
					
					li $v0, 5 #Recebe valorInserido do ususario
					syscall
					move $t2, $v0 # t2 = valorInserido
					
					
					sw $t2, valorInserido
					
					#case valores
					
					beq $t2, 2000, case2000
					exitCase2000:							
					beq $t2, 1000, case1000
					exitCase1000:
					beq $t2, 500, case500
					exitCase500:
					beq $t2, 200, case200
					exitCase200:
					beq $t2, 100, case100
					exitCase100:
					beq $t2, 50, case50
					exitCase50:
					beq $t2, 25, case25
					exitCase25:
					beq $t2, 10, case10
					exitCase10:
					
										
					
				beq $t2, -1, exitWhile
				bgt $t9, $t1, while #while(valorProduto > valorInseridoTotal
			
			
	exitWhile:
	
	
	#imprime valores
	
					
					
	li $v0, 4
	la $a0, trocoMsg
	syscall
					
	jal displayTroco1	
	
	
	sub $t3, $t1, $t9 #t3 = valorInseridoTotal - valorProduto // troco		
		
	
	#se troco existe ou devolver dinheiro na maquina
	bgez    $t2, simTroco # if(troco >= 0)
	fimSimTroco:
	
	bltz  $t2, devolver	#if(troco <=0)
	fimDevolver:	
	
	
	
	
	
	
	#limpa registros
	xor $s0, $s0, $s0
	xor $s1, $s1, $s1
	xor $s2, $s2, $s2
	xor $s3, $s3, $s3
	xor $s4, $s4, $s4
	xor $s5, $s5, $s5
	xor $s6, $s6, $s6
	xor $s7, $s7, $s7
	xor $t9, $t9, $t9
	
			
	
	#aalgoritmo guloso para emissao de troco				

	whileTroco2000: # >= 2000
		ble $t0, 2000, exitWhileTroco2000 
		subi $t0, $t0, 2000 # t0 -=2000
		addi $s0, $s0, 1 #s0++
		lw $t4, reais20 #carrega numero de cedulas em t4
		subi $t4, $t4, 1 #t4-- 
		sw $t4, reais20 #atualiza numero de cedulas
		j whileTroco2000
	exitWhileTroco2000:
		
		
		 
	whileTroco1000:
		ble $t0, 1000, exitWhileTroco1000
		subi $t0, $t0, 1000 # t0 -=1000
		addi $s1, $s1, 1 
		lw $t4, reais10 #carrega numero de cedulas em t4
		subi $t4, $t4, 1 #t4-- 
		sw $t4, reais10 
		j whileTroco1000
	exitWhileTroco1000:
		
		
	whileTroco500:
		ble $t0, 500, exitWhileTroco500
		subi $t0, $t0, 500 
		addi $s2, $s2, 1 
		lw $t4, reais5 #carrega numero de cedulas em t4
		subi $t4, $t4, 1 #t4-- 
		sw $t4, reais5 
		j whileTroco500
	exitWhileTroco500:
		
		
	whileTroco200:
		ble $t0, 200, exitWhileTroco200
		subi $t0, $t0, 200
		addi $s3, $s3, 1 
		lw $t4, reais2 #carrega numero de cedulas em t4
		subi $t4, $t4, 1 #t4-- 
		sw $t4, reais2 
		j whileTroco200
	exitWhileTroco200:
		
		
	whileTroco100:
		ble $t0, 100, exitWhileTroco100
		subi $t0, $t0, 100
		addi $s4, $s4, 1 
		lw $t4, real1 #carrega numero de cedulas em t4
		subi $t4, $t4, 1 #t4-- 
		sw $t4, real1
		j whileTroco100
	exitWhileTroco100:
		
		
	whileTroco50:
		ble $t0, 50, exitWhileTroco50
		subi $t0, $t0, 50
		addi $s5, $s5, 1 
		lw $t4, centavos50 
		subi $t4, $t4, 1 #t4-- 
		sw $t4, centavos50
		j whileTroco50
	exitWhileTroco50:
		
	
	whileTroco25:
		ble $t0, 25, exitWhileTroco25
		subi $t0, $t0, 25
		addi $s6, $s6, 1 
		lw $t4, centavos25
		subi $t4, $t4, 1 #t4-- 
		sw $t4, centavos25
		j whileTroco25
	exitWhileTroco25:
		
		
	
	whileTroco10:
		ble $t0, 10, exitWhileTroco10
		subi $t0, $t0, 10
		addi $s7, $s7, 1 
		lw $t4, centavos10
		subi $t4, $t4, 1 #t4-- 
		sw $t4, centavos10
		j whileTroco10
	exitWhileTroco10:
		
		
	whileTroco5:
		blt $t0, 5, ExitWhileTroco5
		subi $t0, $t0, 5
		addi $t9, $t9, 1 
		lw $t4, centavos5
		subi $t4, $t4, 1 #t4-- 
		sw $t4, centavos5
		j whileTroco5
	ExitWhileTroco5:
		
	
	
	#imprime troco otimizado
	
	
		
	
	
	li $v0, 4
	la $a0, trocoOutMsg
	syscall
	
	li $v0, 4
	la $a0, reais20Msg
	syscall
	
	
	printReais20Msg:
		li $v0, 1
		add $a0, $s0, $zero
		syscall
		
	li $v0, 4
	la $a0, reais10Msg
	syscall
		
		
	printReais10Msg:
		li $v0, 1
		add $a0, $s1, $zero
		syscall
	
	li $v0, 4
	la $a0, reais5Msg
	syscall
	
	printReais5Msg:
		li $v0, 1
		add $a0, $s2, $zero
		syscall
		
		
	li $v0, 4
	la $a0, reais2Msg
	syscall
		
		
	printReais2Msg:
		li $v0, 1
		add $a0, $s3, $zero
		syscall	
	
	
	li $v0, 4
	la $a0, real1Msg
	syscall
	
	printReal1Msg:
		li $v0, 1
		add $a0, $s4, $zero
		syscall
		
		
	li $v0, 4
	la $a0, centavos50Msg
	syscall	
		
	printCentavos50Msg:
		li $v0, 1
		add $a0, $s5, $zero
		syscall
	
	
	li $v0, 4
	la $a0, centavos25Msg
	syscall
	
	printCentavos25Msg:
		li $v0, 1
		add $a0, $s6, $zero
		syscall
	
	li $v0, 4
	la $a0, centavos10Msg
	syscall	
			
					
	printCentavos10Msg:
		li $v0, 1
		add $a0, $s7, $zero
		syscall
	
	li $v0, 4
	la $a0, centavos5Msg
	syscall
	
	printCentavos5Msg:
		li $v0, 1
		add $a0, $t9, $zero
		syscall
	
	
	
	
			
					
	exit:
	#Fim do Programa
	li $v0, 10
	syscall
		
	
	case2000:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s0, $s0, 1 # reais20++	
		sw $0, reais20
		j exitCase2000		
	
	case1000:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s1, $s1, 1 # reais10++
		sw $s1, reais10
		sw $t1, valorInseridoTotal
		j exitCase1000	
		
	case500:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s2, $s2, 1 # reais5++
		sw $s2, reais5
		sw $t1, valorInseridoTotal	
		j exitCase500	
		
	case200:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s3, $s3, 1 # reais2++
		sw $s3, reais2
		sw $t1, valorInseridoTotal	
		j exitCase200		

		
		
	case100:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s4, $s4, 1 # real1++
		sw $s4, real1	
		sw $t1, valorInseridoTotal
		j exitCase100	
		
	case50:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s5, $s5, 1 # centavos50++
		sw $s5, centavos50	
		sw $t1, valorInseridoTotal
		j exitCase50

	case25:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s6, $s6, 1 # centavos25++
		sw $s6, centavos25	
		sw $t1, valorInseridoTotal
		j exitCase25
		
	case10:
		
		add $t1, $t1, $t2  #valorInseridoTotal += valorInserido				
		addi $s7, $s7, 1 # centavos10++
		sw $s7, centavos10	
		sw $t1, valorInseridoTotal
		j exitCase10
			
	
			
	printValorInseridoTotal:
		
		div $t4, $t1, 100
		 
		 mflo $t5 #Quociente
    		 mfhi $t6 #resto
     
     		 #print
    		li $v0, 1
    		add $a0, $zero, $t5
    		syscall
    
    
    		li $v0, 4
    		la $a0, pontoMsg
    		syscall
    
    
   		 #print
   		 mul $t6, $t6, 100
   		 div $t6, $t6, 100
  		 li $v0, 1
   		 add  $a0, $zero, $t6
    		syscall

		
		jr $ra #jump register
	
		
		
	displayValorProduto:
	
		 div $t4, $t9, 100
		 
		 mflo $t5 #Quociente
    		 mfhi $t6 #resto
     
     		 #print
    		li $v0, 1
    		add $a0, $zero, $t5
    		syscall
    
    
    		li $v0, 4
    		la $a0, pontoMsg
    		syscall
    
    
   		 #print
   		 mul $t6, $t6, 100
   		 div $t6, $t6, 100
  		 li $v0, 1
   		 add  $a0, $zero, $t6
    		syscall
    		
		jr $ra #jump register	
		
		


	displayTroco:
	
		sub $t3, $t1, $t9 #t3 = valorInseridoTotal - valorProduto // troco
		mul $t3, $t3, -1
	
		div $t4, $t3, 100
		 
		 mflo $t5 #Quociente
    		 mfhi $t6 #resto
     
     		 #print
    		li $v0, 1
    		add $a0, $zero, $t5
    		syscall
    
    
    		li $v0, 4
    		la $a0, pontoMsg
    		syscall
    
    
   		 #print
   		 mul $t6, $t6, 100
   		 div $t6, $t6, 100
  		 li $v0, 1
   		 add  $a0, $zero, $t6
    		syscall
    		
		jr $ra #jump register
		
		
	displayTroco1:
	
		sub $t3, $t1, $t9 #t3 = valorInseridoTotal - valorProduto // troco
	
		div $t4, $t3, 100
		 
		 mflo $t5 #Quociente
    		 mfhi $t6 #resto
     
     		 #print
    		li $v0, 1
    		add $a0, $zero, $t5
    		syscall
    
    
    		li $v0, 4
    		la $a0, pontoMsg
    		syscall
    
    
   		 #print
   		 mul $t6, $t6, 100
   		 div $t6, $t6, 100
  		 li $v0, 1
   		 add  $a0, $zero, $t6
    		syscall
    		
		jr $ra #jump register	
	
	

		
	simTroco: #troco
		add $t0, $zero, $t3 #t0 valorDevolvido
	
    		
	
    		
    		syscall
		j fimSimTroco
		
	devolver: #devolver dinheiro inserido
		add $t0, $zero, $t1 #t0 valorDevolvido 
	
		
		j fimDevolver	

