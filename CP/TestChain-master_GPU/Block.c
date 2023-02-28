#include "Block.h"
#include "sha256.h"
#include "omp.h"

Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn)
{
    _nNonce = 0;
    _tTime = time(nullptr);

    sHash = _CalculateHash();
}

void Block::MineBlock(uint32_t nDifficulty)
{
    char cstr[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i)
    {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';

    string str(cstr);
	string str2;
	const char* sHash = (char*) malloc (sizeof(char) * 65);
	#pragma omp parallel
	{
		#pragma omp single nowait
		{
			while (str2 != str)
			{
				#pragma omp target data map(tofrom:resp)
				#pragma omp task firstprivate(resp)
				_nNonce++;
				#pragma omp critical(resp)
				sHash = _CalculateHash().c_str();
				string str2(sHash);
				//sHash = _CalculateHash();
			}
		}
	}

    cout << "Block mined: " << string(sHash) << endl;
}

inline string Block::_CalculateHash() const
{
    stringstream ss;
    ss << _nIndex << sPrevHash << _tTime << _sData << _nNonce;

    return sha256(ss.str());
}
