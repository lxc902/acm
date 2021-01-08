########################################################
####                 neoliu                         ####
########################################################
alias cm='cd ~/dev/memesearch/'
alias cdr='cd /home/neoinmtv/go/src/github.com/neoinmtv/draw2meme'
alias v='gvim'
alias vb='v ~/.bashrc && sb'
alias sb='source ~/.bashrc'
function rm {
  mv $@ ~/.local/share/Trash/files/
}
alias open='gnome-open'
alias ana='anaconda-navigator &>/dev/null &'
alias pycharm='/opt/pycharm-community-2019.1.1/bin/pycharm.sh &>/dev/null &'
#alias conda='/home/neoinmtv/anaconda3/bin/conda'
alias b='conda activate bmi260 && cd ~/bmi260'
alias d='cd /home/neoinmtv/go/src/github.com/neoinmtv/draw2meme'
export PATH="$PATH:$HOME/bin"
#export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libgtk3-nocsd.so.0
alias python='python3'
alias pip='pip3'
export PATH=/usr/local/cuda-10.1/bin:/usr/local/cuda-10.1/NsightCompute-2019.1${PATH:+:${PATH}}
#export LD_LIBRARY_PATH=/usr/local/cuda-10.1/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64:/usr/lib/x86_64-linux-gnu
########################################################
####                 neoliu END                     ####
########################################################
