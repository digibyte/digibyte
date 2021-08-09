Bitcoin Upstream Merge Guide
====================================
DigiByte was originally forked from the Bitcoin & Litecoin UTXO codebase. Since 2014 many unique changes have been made to DGB that separate it from the latest BTC codebase. However, there is a tremendous amount of improvements continually being made by talented open-source blockchain developers from around the world to the Bitcoin codebase that DigiByte can quite often benefit from.

Therefore it is important for us to routinely take a look at how some of these improvements can be integrated into the DigiByte codebase in a safe, auditable, reviewable manner. This document is an attempt to document how to best take advantage of those code improvements from Bitcoin with a clearly defined process the community can follow. 

An upstream merge from Bitcoin to DigiByte can be a very complex undertaking for any one person to do alone. There have been several major merge events in DigiBytes history and in the past mistakes have been made during many of these upstream merge events and bugs inadvertently introduced into code. By following the process below many of these issues can be avoided, and the community united in the development process.

3 Approaches To Upstream BTC Merges
------------------------------------
There are roughly 3 different ways to keep DigiByte core up to date with the latest improvements and enhancements to Bitcoin core.

1. Cherry Pick Relelvent commits every 2-4 weeks. By setting a specific day each month, devs can come together and cherry-pick relevant commits that can benefit DGB. If this is done routinely it can prevent mass merge events that are needed after upstream merges are not done for several years.

2. The Bitcoin Rebase. A simple rebase of DGB specific changes onto a fresh Bitcoin clone. While this approach may have worked several years ago that is no longer the case and not recommended. There is a possibility of missing and breaking 100s of things and the only way to verify a release and commit is not breaking unknown and unseen parts of the code is to do a detailed diff comparison between the current stable DGB release and the new rebase, which pretty well leaves you at the third option anyways.

3. The complete Bitcoin/ DigiByte merge. This becomes necessary when routine cherry-pick updates have not been done for some time. This requires an all-hands-on-deck effort and a detailed process that is outlined below. However, this is necessary to provide a clear documented review process for all changes, merge conflicts, and issues that arise. So anyone can publicly verify all changes and the public at large has clear visibility into developer actions. 


Part 1: Pre-Merge Setup (Managed from Source Tree GUI to save time) 
------------------------------------------------------------------------------

1. Completely build latest Bitcoin Core from source all the way to deployment to ensure you have the proper build environment configured. Follow latest BTC dev build environment changes & thoroughly read release notes.

        git clone https://github.com/bitcoin/bitcoin.git
        cd bitcoin	./autogen.sh	./configure 	make

2.  Make Clean directory & make sure no build files are present in clean directory.

        make clean

3.  Rename any text or code string containing: "BTC", "btc," "Bitcoin," "BITCOIN," "bitcoin" w "DGB," "dgb," "DigiByte," "DIGIBYTE," "digibyte" throughout entire codebase with case sensitivity. This is easily done with find & replace inside visual studio code. Should be about 20,000 changes or more. Save each separately and then commit while making sure case sensitivity is on.

4. Commit each separate name swap as its own commit. The idea is to break down the sheer # of name changes in a documented, easy-to-follow process. Not following a consistent naming convention throughout the code easily breaks things and can cause hours of compiler errors later on.

5. Rename all filenames including the text "bitcoin" to "digibyte." This is easily done with finder on Mac. Open folder, use option + over arrow button, then command A to select all. Do this 10 times to open all folders and select all files in the entire code base. Then rename and replace all files containing bitcoin -> digibyte. If all file names are not consistent and everything changed you will get compiler errors later on.

6. Commit all filename changes and save in 1 commit for future reference.

7. Test compile BTC core wallet from scratch with all DGB name changes.

8. Make Clean directory & make sure no build files are present in the clean directory. Will use this branch to merge into the current stable DGB release & devlop branch.

Part 2: The Merge & Merge Conflicts Resolution (The Fun Part)
----------------------------------------------------------------

1.  Select Current DigiByte version as default branch, merge the renamed bitcoin branch you just worked on into DGB core. There will be 1000's of merge conflicts to go through. This is where it is of utmost importance to take your time and go line by line and know what you are changing. Very easy to make a mistake here. Here will be the trouble areas to watch out for. It is important the entire merge with all merge conflicts is committed in 1 commit first so anyone can reflect back on it before any merge conflicts are resolved. The idea is to break down merge resolutions into specific commits in a detailed methodical manner.

2.  Document & note every merge conflict of importance for future reference to look back on what has changed. Useful to learn updates, refactoring, and important changes that can be used to identify bugs when compiling or later on. There will be thousands of trivial name, date, documentation, and other non-essential merge conflicts. Go after these first.

3. Commit Title recommendations for organization of work. Idea is to leave a record easy for anyone to look back on later to see any potential merge issues that have been missed. Label commits starting with the 3 phases "PRE-MERGE:" "MERGE:" & and "COMPILER-FIX:" then include the names of files, the entire folder (if done folder by folder) or the type of functionality changing "Consensus, MultiAlgo, Subsidy, etc."

4. The main merge should be titled something like "MAIN MERGE W/ ALL MERGE CONFLICTS" as it will have to be 1 giant commit in order to document all merge conflicts for future reference.

5. Save all questionable merge conflicts till the end of this process, so everyone has a chance to review together. Typically this has only been a few hundred critical merge conflicts in past mass merges.

6. It is recommended to resolve merge conflicts file by file. So developers can take on a specific file, fix merge conflicts, make the commit, and have others review it. It gets many more people involved and many more eyes on to prevent bugs. Think of it as taking one bite out of the elephant at a time. Take things file by file, commit by commit, merge conflict by merge conflict. The more it is broken down, the easier it is for others to help and to reflect back on later when issues arise.

Key Areas to look out for Merge Conflict / Compiler Bugs: 

	* Anything to do with MultiAlgo
	* Ports, Testnet configs, Genesis block info
	* Protocol Versoning
	* DGB Custom QT GUI Files
	* Private key prefixes (make sure old & new version accepted)
	* DGB address specific prefixes, Bech 32 etc
	* DGB previous hard fork block heights
	* DGB seeds
	* Logos, Icons, and media files, css files.
	* Copyrights (Make sure Bitcoin devs still get all credit they deserve)
	* Dandelion Related Code
	
7. Once all merge conflicts are resolved it's time to get the codebase compiling. If the merge has been done methodically and precisely you might get things to compile first try. However, this has never happened in the past and you will inevitably have many compiler errors to fix.

8. Go error by error and fix each compiler bug and make a commit that clearly explains what was wrong and how it was fixed and how it was broken in the merge. This will help educate everyone else on what to look out for in the future and if there were any other major changes Bitcoin made that break other things in DGB.

9. Once the client is compiling from the command line, now try the GUI and test, test and test some more. Now it's time to get gitian building working.

10. Now that you have a compiling upgraded version of DGB core, pat everyone on the back and go enjoy an ice-cold beer and celebrate.
	

