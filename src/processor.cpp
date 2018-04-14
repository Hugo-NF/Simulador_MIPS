#include "../include/processor.hpp"

processor::processor() {
    this->mem = memory(_big, _hex, _hex);
    this->b_reg = registers();
}

processor::~processor() {
    this->mem.~memory();
    this->b_reg.~registers();
}

void processor::load_memory(const char *path, memory_section sec) {
    fstream file_obj(path, ios::in|ios::binary|ios::ate);
    streampos size;
    char *mem_block;
    unsigned int start = sec == _text? 0: BASE_DATA_ADDRESS;
    unsigned int end = sec == _text? BASE_DATA_ADDRESS:(WORD_SIZE*MEMORY_AMOUNT);

    if(file_obj.is_open()){
        size = file_obj.tellg();
        mem_block = new char[size];
        file_obj.seekg(0, ios::beg);
        file_obj.read(mem_block, size);
        file_obj.close();

        for(uint32_t i = start; i < end; i++){
            this->mem.sb(i,0, (uint8_t)mem_block[i]);
        }

        delete[] mem_block;
    }
    else
        printf(UNKNOWN_FILE);
}

void processor::fetch() {
    if(b_reg.PC < BASE_DATA_ADDRESS) {
        b_reg.RI = (uint32_t) mem.lw(b_reg.PC, 0);
        b_reg.update_pc(_word);
    }
    else
        throw out_of_range(PC_OUT_OF_BOUNDS);
}

void processor::decode() {
    this->inst_fields.opcode = (uint8_t)(b_reg.RI>>26);
    this->inst_fields.rs = (uint8_t)((b_reg.RI>>21) & 0x0000001F);
    this->inst_fields.rt = (uint8_t)((b_reg.RI>>16) & 0x0000001F);
    this->inst_fields.rd = (uint8_t)((b_reg.RI>>11) & 0x0000001F);
    this->inst_fields.shammt = (uint8_t)((b_reg.RI>>6) & 0x0000001F);
    this->inst_fields.funct = (uint8_t)((b_reg.RI) & 0x0000003F);
    this->inst_fields.k16 = (int16_t) (b_reg.RI & 0x0000FFFF);
    this->inst_fields.k26 = (uint32_t) (b_reg.RI & 0x03FFFFFF);
}

void processor::execute() {
    switch (this->inst_fields.opcode){
        case EXT:
            switch (this->inst_fields.funct){
                case ADD:
                    this->add();
                    break;
                case SUB:
                    this->sub();
                    break;
                case MULT:
                    this->mult();
                    break;
                case DIV:
                    this->div();
                    break;
                case AND:
                    this->_and();
                    break;
                case OR:
                    this->_or();
                    break;
                case XOR:
                    this->_xor();
                    break;
                case NOR:
                    this->nor();
                    break;
                case SLT:
                    this->slt();
                    break;
                case JR:
                    this->jr();
                    break;
                case SLL:
                    this->sll();
                    break;
                case SRL:
                    this->srl();
                    break;
                case SRA:
                    this->sra();
                    break;
                case SYSCALL:
                    this->syscall();
                    break;
                case MFHI:
                    this->mfhi();
                    break;
                case MFLO:
                    this->mflo();
                    break;
                default:
                    throw logic_error(UNKNOWN_OPCODE);
            }
        case LW:
            this->lw();
            break;
        case LB:
            this->lb();
            break;
        case LBU:
            this->lbu();
            break;
        case LH:
            this->lh();
            break;
        case LHU:
            this->lhu();
            break;
        case LUI:
            this->lui();
            break;
        case SW:
            this->sw();
            break;
        case SB:
            this->sb();
            break;
        case SH:
            this->sh();
            break;
        case BEQ:
            this->beq();
            break;
        case BNE:
            this->bne();
            break;
        case BLEZ:
            this->blez();
            break;
        case BGTZ:
            this->bgtz();
            break;
        case ADDI:
            this->addi();
            break;
        case SLTI:
            this->slti();
            break;
        case SLTIU:
            this->sltiu();
            break;
        case ANDI:
            this->andi();
            break;
        case ORI:
            this->ori();
            break;
        case XORI:
            this->xori();
            break;
        case J:
            this->j();
            break;
        case JAL:
            this->jal();
            break;
        default:
            throw logic_error(UNKNOWN_OPCODE);
    }
}

