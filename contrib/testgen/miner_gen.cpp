    pblocktemplate->block.hashPrevBlock = uint256S("7497ea1b465eb39f1c8f507bc877078fe016d6fcb6dfad3a64c98dcc6e1e8496");

    while(true) {
        CBlock *pblock = &pblocktemplate->block; // pointer for convenience
        std::cout << pblock->hashPrevBlock.ToString() << std::endl;
        std::cout << chainActive.Tip()->GetBlockHash().ToString() << std::endl;
        std::cout << "H:" << chainActive.Tip()->nHeight << std::endl;

        pblock->nVersion = 1;
        pblock->nTime = chainActive.Tip()->GetMedianTimePast()+1;
        // pblock->nBits = UintToArith256(uint256S("7ffff00000000000000000000000000000000000000000000000000000000000")).GetCompact();
    //       CMutableTransaction txCoinbase(*pblock->vtx[0]);
        bool processBlock = false;
        unsigned int a = 17000000;

        while (!processBlock) {
            pblock->nNonce = a++;
            if(a % 100000 == 0) {
                std::cout << "at count " << a << std::endl;
            }

            for(int j=1; j<7; j++) {
        //            CBlock *pblock = &pblocktemplate->block; // pointer for convenience
        //            pblock->nVersion = 1;
        //            pblock->nTime = chainActive.Tip()->GetMedianTimePast()+1;
                CMutableTransaction txCoinbase(*pblock->vtx[0]);
                txCoinbase.nVersion = 1;
                txCoinbase.vin[0].scriptSig = CScript();
                txCoinbase.vin[0].scriptSig.push_back(j); //blockinfo[i].extranonce);
                txCoinbase.vin[0].scriptSig.push_back(chainActive.Height());
                txCoinbase.vout.resize(1); // Ignore the (optional) segwit commitment added by CreateNewBlock (as the hardcoded nonces don't account for this)
                txCoinbase.vout[0].scriptPubKey = CScript();
                pblock->vtx[0] = MakeTransactionRef(std::move(txCoinbase));
                if (txFirst.size() == 0)
                    baseheight = chainActive.Height();
                if (txFirst.size() < 4)
                    txFirst.push_back(pblock->vtx[0]);
                pblock->hashMerkleRoot = BlockMerkleRoot(*pblock);
                //pblock->nNonce = blockinfo[i].nonce;
                std::shared_ptr<const CBlock> shared_pblock = std::make_shared<const CBlock>(*pblock);
                processBlock = ProcessNewBlock(chainparams, shared_pblock, true, nullptr);
                //BOOST_CHECK(processBlock);
                if(processBlock) {
                      std::cout << "nounce is " << shared_pblock->nNonce << std::endl;
                    std::cout << "extra nounce is " << j << std::endl;
                    break;
                }
            }
        }
        //  std::shared_ptr<const CBlock> shared_pblock = std::make_shared<const CBlock>(*pblock);
        //  bool processBlock = ProcessNewBlock(chainparams, shared_pblock, true, nullptr);
        //   BOOST_CHECK(ProcessNewBlock(chainparams, shared_pblock, true, nullptr));
        pblock->hashPrevBlock = pblock->GetHash();
    }

    return;