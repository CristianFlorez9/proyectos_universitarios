module topROM #(
    parameter FPGAFREQ = 900_000  // Frecuencia para ajustar velocidad de los soldados

)(
    input  logic        CLK,
    input  logic        nRST,
    input  logic        nPBTON,
    input  logic        sw1,
    input  logic        sw2,
    output logic        HS,
    output logic        VS,
    output logic [11:0] RGB,
    input  logic        clk,
    input  logic        rst,
    input  logic [3:0]  COLUMNAS,   // Entradas de columnas del teclado
    output logic [3:0]  FILAS,      // Filas activadas por el controlador
    output logic [3:0]  TECLA,      // Código de tecla detectada (0-F)
    input  logic [3:0]  COLUMNASX,  // Entradas de columnas del segundo teclado
    output logic [3:0]  FILASX,     // Filas activadas por el segundo controlador
    output logic [3:0]  TECLAX,     // Código de tecla detectada (0-F) - segundo teclado
    output logic        FLAGX,      // Flag alto cuando se detecta una tecla
    output reg          btn_up1 = 1'b0,    // Botón para mover hacia arriba (jugador 1)
    output reg          btn_down1 = 1'b0,  // Botón para mover hacia abajo (jugador 1)
    output reg          proyectil_1 = 1'b0,
    output reg          btn_up2 = 1'b0,    // Botón para mover hacia arriba (jugador 2)
    output reg          btn_down2 = 1'b0,  // Botón para mover hacia abajo (jugador 2)
    output reg          proyectil_2 = 1'b0
);

    // Parámetros base Teclado
    localparam int DELAY_1MS  = 10000;
    localparam int DELAY_10MS = 125000;
   // parametros  de display 34
	
	// Cada uno de estos encenderá un solo segmento.
	localparam [33:0] A = 34'b1111001111000011110000000000000000;
	localparam [33:0] N = 34'b1100001111000011110000000000000000;
	localparam [33:0] F = 34'b1111001111000000000000000000000000;
	

	localparam [33:0] C = 34'b1100111111000000000000000000000000;
	localparam [33:0] R =34'b1111001111000011000000100100000000;
	localparam [33:0] I = 34'b1100110000111100000000000000000000;
	
        


    logic [2:0] SPEED;
    localparam int BITS_1MS  = $clog2(DELAY_1MS);
    localparam int BITS_10MS = $clog2(DELAY_10MS);

    logic [BITS_1MS-1:0]  conta_1ms;
    logic [BITS_10MS-1:0] conta_10ms;

    // Registros para anti-rebote
    logic [7:0] REG0, REG1, REG2, REG3;
    logic [7:0] FILACOL;
    logic [3:0] SCOL;

    // Registros para segundo teclado
    logic [7:0] REG0X, REG1X, REG2X, REG3X;
    logic [7:0] FILACOLX;
    logic [3:0] SCOLX;

    // Señales de control
    logic clkout, clkout2;
    logic b, bX;
    logic [1:0] CONT, CONTX;
    logic [9:0] counter1 = 10'd0, counter2 = 10'd0;

    //--------------------------------------------------------------------------
    // Lógica de anti-rebote para teclados
    //--------------------------------------------------------------------------
   
    // Divisor de reloj para anti-rebote (1ms)
    always @(posedge CLK) begin
        if (~rst) begin
            conta_1ms <= 0;
            clkout2 <= 0;
        end else begin
            conta_1ms <= conta_1ms + 1'b1;
            if (conta_1ms == DELAY_1MS - 1) begin
                clkout2 <= ~clkout2;
                conta_1ms <= 0;
            end    
        end    
    end

    // Divisor de reloj principal (10ms)
    always @(posedge CLK) begin
        if (~rst) begin
            conta_10ms <= 0;
            clkout <= 0;
        end else begin
            conta_10ms <= conta_10ms + 1'b1;
            if (conta_10ms == DELAY_10MS - 1) begin
                clkout <= ~clkout;
                conta_10ms <= 0;
            end    
        end    
    end        

    // Anti-rebote para columnas del primer teclado
    always_ff @(posedge clkout2) begin
        REG0 <= {REG0[6:0], COLUMNAS[0]};
        REG1 <= {REG1[6:0], COLUMNAS[1]};
        REG2 <= {REG2[6:0], COLUMNAS[2]};
        REG3 <= {REG3[6:0], COLUMNAS[3]};
     
        SCOL[0] <= (REG0 == 8'b11111111) ? 1'b1 : 1'b0;
        SCOL[1] <= (REG1 == 8'b11111111) ? 1'b1 : 1'b0;
        SCOL[2] <= (REG2 == 8'b11111111) ? 1'b1 : 1'b0;
        SCOL[3] <= (REG3 == 8'b11111111) ? 1'b1 : 1'b0;
       
        b <= SCOL[0] | SCOL[1] | SCOL[2] | SCOL[3];
    end

    // Anti-rebote para columnas del segundo teclado
    always_ff @(posedge clkout2) begin
        REG0X <= {REG0X[6:0], COLUMNASX[0]};
        REG1X <= {REG1X[6:0], COLUMNASX[1]};
        REG2X <= {REG2X[6:0], COLUMNASX[2]};
        REG3X <= {REG3X[6:0], COLUMNASX[3]};
     
        SCOLX[0] <= (REG0X == 8'b11111111) ? 1'b1 : 1'b0;
        SCOLX[1] <= (REG1X == 8'b11111111) ? 1'b1 : 1'b0;
        SCOLX[2] <= (REG2X == 8'b11111111) ? 1'b1 : 1'b0;
        SCOLX[3] <= (REG3X == 8'b11111111) ? 1'b1 : 1'b0;
       
        bX <= SCOLX[0] | SCOLX[1] | SCOLX[2] | SCOLX[3];
    end

    // Flags de detección de teclas
    assign FLAG  = b;
    assign FLAGX = bX;

    // Captura de combinación FILA-COLUMNA
    always_ff @(posedge b) begin
        if (~rst) begin
            FILACOL <= 8'b00000000;
        end else begin
            FILACOL <= {FILAS, SCOL};
        end
    end

    always_ff @(posedge bX) begin
        if (~rst) begin
            FILACOLX <= 8'b00000000;
        end else begin
            FILACOLX <= {FILASX, SCOLX};
        end
    end

    // Control de barrido de filas
    always @(posedge clkout) begin
        if (~rst) begin
            CONT <= 1'd0;
            FILAS <= 4'b0001;
        end else begin
            CONT <= CONT + 1'd1;
            FILAS <= 4'b0001 << CONT;
        end
    end

    always @(posedge clkout) begin
        if (~rst) begin
            CONTX <= 1'd0;
            FILASX <= 4'b0001;
        end else begin
            CONTX <= CONTX + 1'd1;
            FILASX <= 4'b0001 << CONTX;
        end
    end

    //--------------------------------------------------------------------------
    // Lógica de controles para jugadores
    //--------------------------------------------------------------------------

    // Mapeo de teclas para jugador 1
    always_comb begin
        case (FILACOL)
            8'b00100001: begin  // Tecla específica para arriba
                btn_up1   = 1'b1;
                btn_down1 = 1'b0;
            end
            8'b00100010: begin  // Tecla específica para abajo
                btn_up1   = 1'b0;
                btn_down1 = 1'b1;
            end
            8'b00101000: begin  // Tecla específica para disparar
                btn_up1   = 1'b0;
                btn_down1 = 1'b0;
            end
            default: begin
                btn_up1   = 1'b0;
                btn_down1 = 1'b0;
            end
        endcase
    end

    // Mapeo de teclas para jugador 2
    always_comb begin
        case (FILACOLX)
            8'b00100001: begin  // Tecla específica para arriba
                btn_up2   = 1'b1;
                btn_down2 = 1'b0;
            end
            8'b00100010: begin  // Tecla específica para abajo
                btn_up2   = 1'b0;
                btn_down2 = 1'b1;
            end
            8'b00101000: begin  // Tecla específica para disparar
                btn_up2   = 1'b0;
                btn_down2 = 1'b0;
            end
            default: begin
                btn_up2   = 1'b0;
                btn_down2 = 1'b0;
            end
        endcase
    end  

    //--------------------------------------------------------------------------
    // Señales de control generadas
    //--------------------------------------------------------------------------
    logic RST;
    logic PBTON;
    assign RST   = ~nRST;
    assign PBTON = ~nPBTON;

    //--------------------------------------------------------------------------
    // Lógica del juego - Posiciones y movimientos
    //--------------------------------------------------------------------------
   
    // Posición de soldados y proyectiles
    logic [10:0] soldado1_y  = 11'd100;
    logic [10:0] soldado2_y  = 11'd300;
    logic [10:0] proyectil1_x = 11'd20;
    logic [10:0] proyectil1_y;
    logic signed [10:0] proyectil2_x = 11'd400;
    logic [10:0] proyectil2_y;

    // Contadores para marcadores
    logic [3:0] units, tens, units2, tens2;

    //--------------------------------------------------------------------------
    // Subsistema VGA
    //--------------------------------------------------------------------------
   
    // Señales VGA
    logic [11:0] rgb_aux, rgb_barra1, rgb_barra2;
    logic [10:0] hcount, vcount;
    logic blank;

    // Señales de dibujo
    logic PAINTU, PAINTD, PAINTC, PAINTS;
    logic PAINT134SEG, PAINT234SEG, PAINT334SEG, PAINT434SEG;
    logic paintImg1, paintImg2, paintImg3, paintImg4;

    // Divisor de reloj para el juego
    logic clkdiv0;
    cntdiv_n #(FPGAFREQ) cntDiv0(CLK, RST, clkdiv0);



    // Instancia del controlador VGA
    vga_ctrl_640x480_60Hz vga_ctrl_inst (
        .rst(RST),
        .clk(CLK),
        .rgb_in(rgb_aux),
        .HS(HS),
        .VS(VS),
        .hcount(hcount),
        .vcount(vcount),
        .rgb_out(RGB),
        .blank(blank)
    );

    // Instancias de displays para marcadores
    display #(5, 30, 40, 10) displayU(hcount, vcount, tens, PAINTU);    // decenas izq
    display #(5, 30, 40, 50) displayD(hcount, vcount, units, PAINTD);   // unidades izq
    display #(5, 30, 40, 600) displayC(hcount, vcount, units2, PAINTC);    // unidades der
    display #(5, 30, 40, 560) displayS(hcount, vcount, tens2, PAINTS);     // decenas der

    // Displays grandes decorativos
    display34segm #(4, 50) display1(110, 2, A, hcount, vcount, PAINT1SEG);
    display34segm #(4, 50) display2(160, 2, N, hcount, vcount, PAINT2SEG);
    display34segm #(4, 50) display3(210, 2, F, hcount, vcount, PAINT3SEG);
    
	 
    display34segm #(4, 50) display5(400, 2, C, hcount, vcount, PAINT4SEG);
    display34segm #(4, 50) display6(450, 2, R, hcount, vcount, PAINT5SEG);
    display34segm #(4, 50) display7(500, 2, I, hcount, vcount, PAINT6SEG);
     

    // Instancias de sprites para elementos del juego
    image drawImg1(
        .POSX(proyectil2_x),
        .pos_y(proyectil2_y),
        .pix_x(hcount),
        .pix_y(vcount),
        .paint(paintImg1)
    );

    imageROM1 drawImg2(
        .POSX(proyectil1_x),
        .pos_y(proyectil1_y),
        .pix_x(hcount),
        .pix_y(vcount),
        .paint(paintImg2)
    );

    imageROM2 drawImg3(
        .POSX(11'd590),
        .pos_y(soldado1_y),
        .pix_x(hcount),
        .pix_y(vcount),
        .paint(paintImg3)
    );

    imageROM3 drawImg4(
        .POSX(11'd20),
        .pos_y(soldado2_y),
        .pix_x(hcount),
        .pix_y(vcount),
        .paint(paintImg4)
    );

    // Barreras laterales del campo de juego
    draw_square barra1(
        .posicion_xmin(11'd0),
        .posicion_xmax(11'd9),
        .posicion_ymim(11'd80),
        .posicion_ymax(11'd440),
        .pix_x(hcount),
        .pix_y(vcount),
        .rgb_int(12'hF00),
        .color_fondo(12'h000),
        .rgb_out(rgb_barra1)
    );

    draw_square barra2(
        .posicion_xmin(11'd630),
        .posicion_xmax(11'd639),
        .posicion_ymim(11'd80),
        .posicion_ymax(11'd440),
        .pix_x(hcount),
        .pix_y(vcount),
        .rgb_int(12'h3F2),
        .color_fondo(12'h000),
        .rgb_out(rgb_barra2)
    );

    // Lógica de selección de color para VGA
    always_comb begin
        rgb_aux = 12'h000;  // Fondo negro por defecto
       
        // Prioridades de dibujo
        if (PAINTC)
            rgb_aux = 12'hFF0;  // Amarillo - unidades derecha
        else if (PAINTD || PAINTS)
            rgb_aux = 12'h00F;  // Azul - unidades izquierda o decenas derecha
        else if (PAINTU)
            rgb_aux = 12'hF00;  // Rojo - decenas izquierda
        else if (PAINT1SEG || PAINT2SEG || PAINT3SEG || PAINT4SEG || PAINT5SEG || PAINT6SEG)
            rgb_aux = 12'h0F0;  // Verde - displays grandes
        else if (paintImg1 || paintImg2 || paintImg3 || paintImg4)
            rgb_aux = 12'hB4A;  // Color especial para sprites
        else if (rgb_barra1 != 12'h000)
            rgb_aux = rgb_barra1;  // Color de barra izquierda
        else if (rgb_barra2 != 12'h000)
            rgb_aux = rgb_barra2;  // Color de barra derecha
    end
    //--------------------------------------------------------------------------
    // Lógica principal del juego
    //--------------------------------------------------------------------------
   
    // Movimiento de los soldados/jugadores
    always_ff @(posedge clkdiv0 or posedge RST) begin
        if (RST) begin
            // Reset de posiciones
            soldado1_y <= 11'd100;
            soldado2_y <= 11'd300;
            SPEED <= 3'b0;
        end else begin
            // Configuración de velocidad según switches
            SPEED <= ((sw2 << 1) + sw1) + 1;
           
            // Control soldado 1 (derecha)
            if (btn_up1 && soldado1_y > 90) begin
                soldado1_y <= soldado1_y - 1;       // Mover arriba
            end else if (btn_down1 && soldado1_y < 410) begin
                soldado1_y <= soldado1_y + 1;       // Mover abajo
            end

            // Control soldado 2 (izquierda)
            if (btn_up2 && soldado2_y > 90) begin
                soldado2_y <= soldado2_y - 1;       // Mover arriba
            end else if (btn_down2 && soldado2_y < 410) begin
                soldado2_y <= soldado2_y + 1;       // Mover abajo
            end
        end
    end

    // Conversión de contadores a dígitos para displays
    always_comb begin
        units  = (counter1 % 10);       // Unidades jugador 1
        tens   = ((counter1 / 10) % 10); // Decenas jugador 1
        units2 = (counter2 % 10);       // Unidades jugador 2
        tens2  = ((counter2 / 10) % 10); // Decenas jugador 2
    end

    // Señales de colisión
    logic colision_barra_de_jugador1 = 0;
    logic colision_barra_de_jugador2 = 0;

    // Lógica de proyectiles
	always_ff @(posedge clkdiv0 or posedge RST) begin
		if (RST) begin
        // Reset de proyectiles
        proyectil1_x <= 11'd20;
        proyectil2_y <= 11'd100;
        proyectil1_y <= 11'd300;
        proyectil2_x <= 11'd600;
        proyectil_1  <= 1'b0;
        proyectil_2  <= 1'b0;
		  counter1 <= 0;
		  counter2 <= 0;
        colision_barra_de_jugador1 <= 0;
        colision_barra_de_jugador2 <= 0;
		end else begin
        // Activación de disparo jugador 2 (derecha)
        if (FILACOL == 8'b00101000 && ~proyectil_2 && b) begin
            proyectil_2 <= 1'b1;
            proyectil2_y <= soldado1_y;
				proyectil2_x <= 600;
        end

        // Activación de disparo jugador 1 (izquierda)
        if (FILACOLX == 8'b00101000 && ~proyectil_1 && bX) begin
            proyectil_1 <= 1'b1;
            proyectil1_y <= soldado2_y;
				proyectil1_x <= 20;
        end

        // Movimiento proyectil 1 (derecha)
        if (proyectil_1) begin
            if (proyectil1_x < 610) begin
                proyectil1_x <= proyectil1_x + SPEED;
            end else begin
                // Colisión con límite derecho
                colision_barra_de_jugador2 <= 1;

                if (colision_barra_de_jugador2) begin
                    counter1 <= (counter1 == 999) ? 0 : counter1 + 2;
                    colision_barra_de_jugador2 <= 0;
                    proyectil1_x <= 20;
                    proyectil_1 <= 1'b0;
                end
            end
        end else begin
            proyectil1_y <= soldado2_y;
				proyectil1_x <= 20;
        end

        // Lógica entre balas (hitbox)
        if (proyectil_1 && proyectil_2) begin
		  
            if ((proyectil1_x < proyectil2_x + 32) &&
                (proyectil1_x + 32 > proyectil2_x) &&
                (proyectil1_y < proyectil2_y + 16) &&
                (proyectil1_y + 16 > proyectil2_y)) begin

                // se detecta bala interceptadora
					if(proyectil1_x > 320) begin 
						counter2 <= (counter2 == 999) ? 0 : counter2 + 1;
					end 
							
					else if (proyectil2_x < 320) begin 
						counter1 <= (counter1 == 999) ? 0 : counter1 + 1;
					end
						
					else if (proyectil1_x == proyectil2_x) begin 
						counter1 <= (counter1 == 999) ? 0 : counter1 + 1;
						counter2 <= (counter2 == 999) ? 0 : counter2 + 1;
					end
               

                // Reiniciar posiciones
					proyectil1_y <= soldado1_y;
					proyectil1_x <= 20;
					proyectil_1 <= 0;

					proyectil2_y <= soldado2_y;
					proyectil2_x <= 600;
					proyectil_2 <= 0;
					
            end
        end

        // Lógica colisión bala 1 - sprite 2
        if (proyectil_1) begin
            if ((proyectil1_x < 550 + 30) &&
                (proyectil1_x + 32 > 11'd550) &&
                (proyectil1_y < soldado1_y + 24) &&
                (proyectil1_y + 16 > soldado1_y)) begin

					//se detecta colision

               proyectil1_y <= soldado1_y;
					proyectil1_x <= 20;
					proyectil_1 <= 0;
            end
        end
 
	if (proyectil_2) begin
		if ((proyectil2_x < 20 + 40) &&
			(proyectil2_x + 32 > 20) &&
			(proyectil2_y < soldado2_y + 24) &&
			(proyectil2_y + 16 > soldado2_y)) begin

         proyectil2_y <= soldado2_y;
			proyectil2_x <= 20;
			proyectil_2 <= 0; // Reinicio de posición (lado derecho)
		end
	end

        // Movimiento proyectil 2 (izquierda)
        if (proyectil_2) begin
            if (proyectil2_x > 0) begin
                proyectil2_x <= proyectil2_x - SPEED;
            end else begin
                // Colisión con límite derecho
					counter2 <= (counter2 == 999) ? 0 : counter2 + 2;
					proyectil2_x <= 600;         // Reinicia a la derecha
					proyectil2_y <= soldado1_y; // O posición inicial
					proyectil_2  <= 0;           // Desactiva proyectil
            end
        end else begin
            proyectil2_y <= soldado1_y;
				proyectil2_x <= 600;
        end
		end
	end




endmodule