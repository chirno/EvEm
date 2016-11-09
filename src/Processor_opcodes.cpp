#include "../include/Processor.h"

void Processor::ProcessOpcode(uint8_t code)
{
    uint8_t temp = this->PC->GetByte(0);
    if (temp == 0xFF)
    {
        this->PC->SetByte(0, 0x00);
        temp = this->PC->GetByte(1);
        if (temp == 0xFF)
            this->PC->SetByte(1, 0x00);
        else
            this->PC->SetByte(1, temp + 1);
    }
    else
        this->PC->SetByte(0, temp + 1);

    unsigned int m = 0, t = 0;
    (*operations)[code](this);
    this->mTotal += this->M->GetByte(0);
    this->tTotal += this->T->GetByte(0);
    // Increment program counter and prevent it from going over limit?
}

void Processor::InitOpcodes()
{
    operations = new std::unordered_map<uint8_t, std::function<void(Processor* p)>>();
    (*operations)[0x00] = [](Processor* p) {
        p->NOP();
    };
    (*operations)[0x01] = [](Processor* p) {
        uint16_t immediate = ((uint16_t)p->PC->GetByte(1) << 8) | p->PC->GetByte(0);
        p->Load(p->B, p->C, p->memory->GetByte(p->PC->GetWord(0)));
    };
    (*operations)[0x02] = [](Processor* p) {
        p->Store(p->A, p->B, p->C);
    };
    (*operations)[0x03] = [](Processor* p) {
        p->INC(p->B, p->C);
    };
    (*operations)[0x04] = [](Processor* p) {
        p->INC(p->B);
    };
    (*operations)[0x05] = [](Processor* p) {
        p->DEC(p->B);
    };
    (*operations)[0x06] = [](Processor* p) {
        p->Load(p->B, p->memory->GetByte(p->PC->GetWord(0)));
        p->PC->Increment();
    };
    (*operations)[0x07] = [](Processor* p) {
        p->RLC(p->A);
    };
    (*operations)[0x08] = [](Processor* p) {
        uint16_t word = p->PC->GetWord(0);
        p->Store(p->SP, p->memory->GetWord(word));
        p->PC->SetWord(0, word + 2);
    };
    (*operations)[0x09] = [](Processor* p) {
        p->ADD(p->B, p->C, p->H, p->L);
    };
    (*operations)[0x0A] = [](Processor* p) {
        p->Load(p->A, p->B, p->C);
    };
    (*operations)[0x0B] = [](Processor* p) {
        p->DEC(p->B, p->C);
    };
    (*operations)[0x0C] = [](Processor* p) {
        p->INC(p->C);
    };
    (*operations)[0x0D] = [](Processor* p) {
        p->DEC(p->C);
    };
    (*operations)[0x0E] = [](Processor* p) {
        p->Load(p->C, p->memory->GetByte(p->PC->GetWord(0)));
        p->PC->Increment();
    };
    (*operations)[0x0F] = [](Processor* p) {
        p->RRC(p->A);
    };
    (*operations)[0x10] = [](Processor* p) {
        p->STOP();
    };
    (*operations)[0x11] = [](Processor* p) {
        uint16_t immediate = ((uint16_t)p->PC->GetByte(1) << 8) | p->PC->GetByte(0);
        p->Load(p->D, p->E, immediate);
    };
    (*operations)[0x12] = [](Processor* p) {

    };
    (*operations)[0x13] = [](Processor* p) {

    };
    (*operations)[0x14] = [](Processor* p) {

    };
    (*operations)[0x15] = [](Processor* p) {

    };
    (*operations)[0x16] = [](Processor* p) {

    };
    (*operations)[0x17] = [](Processor* p) {

    };
    (*operations)[0x18] = [](Processor* p) {

    };
    (*operations)[0x19] = [](Processor* p) {

    };
    (*operations)[0x20] = [](Processor* p) {

    };
    (*operations)[0x21] = [](Processor* p) {

    };
    (*operations)[0x80] = [](Processor* p) {
        p->ADD(p->A, p->B);
    };
}
