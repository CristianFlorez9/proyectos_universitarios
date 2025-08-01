module imageROM1 (
    
    input logic [10:0] POSX,
	 input logic [10:0] pos_y,
    input logic [10:0] pix_x,
    input logic [10:0] pix_y,
    output logic paint
);

    // Declaración de señales internas
    logic [3:0] addRom_sig; //Row
    logic [31:0] dataRom_sig; //Col

    // Constantes para el tamaño de la ROM
    localparam int sizeColRom = 32;
    localparam int sizeRowRom = 16;

    // Instancia de la ROM (componente imageROM)
    ROM1 img1 (addRom_sig,dataRom_sig);

    // Proceso para dibujar la imagen almacenada en la ROM
    always_comb begin
		  addRom_sig = 4'b0000;
		  paint = 1'b0;
        if ((pix_y >= pos_y) && (pix_y < (pos_y + sizeRowRom)) && 
            (pix_x >= POSX) && (pix_x < (POSX + sizeColRom))) 
        begin
            addRom_sig = 4'(pix_y - pos_y);
            paint = dataRom_sig[~(pix_x - POSX)];
        end
    end

endmodule