#include "transition.h"

TransitionBlock::TransitionBlock()
{
  out_block_input_ = new NodeInput("out_block_in");
  out_block_input_->set_data_type(NodeParam::kBuffer);
  AddInput(out_block_input_);

  in_block_input_ = new NodeInput("in_block_in");
  in_block_input_->set_data_type(NodeParam::kBuffer);
  AddInput(in_block_input_);
}

Block::Type TransitionBlock::type() const
{
  return kTransition;
}

QString TransitionBlock::Category() const
{
  return tr("Transition");
}

NodeInput *TransitionBlock::out_block_input() const
{
  return out_block_input_;
}

NodeInput *TransitionBlock::in_block_input() const
{
  return in_block_input_;
}

void TransitionBlock::Retranslate()
{
  out_block_input_->set_name(tr("From"));
  in_block_input_->set_name(tr("To"));
}

void TransitionBlock::set_length(const rational &length)
{
  Q_UNUSED(length)
  qCritical() << "Set length is not permitted on a transition";
  abort();
}

void TransitionBlock::set_length_and_media_in(const rational &length)
{
  Q_UNUSED(length)
  qCritical() << "Set length and media in is not permitted on a transition";
  abort();
}

void TransitionBlock::set_in_offset(const rational &in_offset)
{
  in_offset_ = in_offset;
  RecalculateLength();
}

void TransitionBlock::set_out_offset(const rational &out_offset)
{
  out_offset_ = out_offset;
  RecalculateLength();
}

void TransitionBlock::RecalculateLength()
{
  Block::set_length(in_offset_ + out_offset_);
}
