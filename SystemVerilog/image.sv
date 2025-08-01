module image (
    input logic [10:0] POSX,
    input logic [10:0] pos_y,
    input logic [10:0] pix_x,
    input logic [10:0] pix_y,
    output logic paint
);

    // Tamaño de la imagen ROM
    localparam int sizeColRom = 32;
    localparam int sizeRowRom = 16;

    logic [3:0] addRom_sig;         // dirección fila (y)
    logic [31:0] dataRom_sig;       // datos columna (x)

    // Instancia de ROM
    ROM0 img0 (
        .addRom(addRom_sig),
        .dataRom(dataRom_sig)
    );

    always_comb begin
        addRom_sig = 4'd0;
        paint = 1'b0;

        if ((pix_y >= pos_y) && (pix_y < (pos_y + sizeRowRom)) &&
            (pix_x >= POSX)  && (pix_x < (POSX + sizeColRom))) begin
            addRom_sig = pix_y - pos_y;
            paint = dataRom_sig[~(pix_x - POSX)];
        end
    end

endmodule






